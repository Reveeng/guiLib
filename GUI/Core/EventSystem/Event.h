#ifndef EVENT_H
#define EVENT_H

#include <functional>
#include <inttypes.h>
#include <condition_variable>

class AbstractEvent
{
public:
    AbstractEvent();
    virtual ~AbstractEvent();
    virtual void executeCallback() = 0;
};

template  <typename... Args>
class Event : public AbstractEvent
{
public:
    Event():
        AbstractEvent()
    {

    }
    Event(std::function<void(Args...)> cb,
          Args... args):
        AbstractEvent(),
        m_args(std::make_tuple(std::forward<Args>(args)...)),
        m_callback(cb)
    {

    }
    Event(Event &o):
        AbstractEvent(o),
        m_args(o.m_args),
        m_callback(o.m_callback)
    {

    }
    Event(Event &&o):
        AbstractEvent(o),
        m_args(std::move(o.m_args)),
        m_callback(std::move(o.m_callback))
    {

    }
    ~Event()
    {

    }
    void setData(Args&... args)
    {
        m_args = std::make_tuple(std::forward<Args>(args)...);
    }
    virtual void executeCallback() override{
        std::apply(m_callback,m_args);
    }

private:
    std::tuple<Args...> m_args;
    std::function<void(Args...)> m_callback;
};


//work only with atomic types
template <typename T>
class WaitableEvent : public AbstractEvent{
public:
    WaitableEvent():
        AbstractEvent(),
        m_valueStorage(new T),
        m_syncCV(new std::condition_variable),
        m_cvMutex(new std::mutex)
    {

    }
    WaitableEvent(std::function<T()> cb):
        AbstractEvent(),
        m_eventCallback(cb),
        m_valueStorage(new T),
        m_syncCV(new std::condition_variable),
        m_cvMutex(new std::mutex)
    {

    }
    WaitableEvent(const WaitableEvent &o):
        AbstractEvent(o),
        m_eventCallback(o.m_eventCallback),
        m_valueStorage(o.m_valueStorage),
        m_syncCV(o.m_syncCV),
        m_cvMutex(o.m_cvMutex)
    {

    }
    WaitableEvent(WaitableEvent &&o):
        AbstractEvent(o),
        m_eventCallback(std::move(o.m_eventCallback)),
        m_valueStorage(std::move(o.m_valueStorage)),
        m_syncCV(std::move(o.m_syncCV)),
        m_cvMutex(std::move(o.m_cvMutex))
    {

    }

    ~WaitableEvent(){

    }

    virtual void executeCallback() override
    {
        T* ptr = m_valueStorage.get();
        *ptr = m_eventCallback();
        m_syncCV->notify_all();
    }
    T waitEventExecution()
    {
        std::unique_lock lk(*m_cvMutex);
        m_syncCV->wait(lk);
        return *m_valueStorage;
    }

private:
    std::function<T()> m_eventCallback;

    std::shared_ptr<T> m_valueStorage;

    std::shared_ptr<std::condition_variable> m_syncCV;
    std::shared_ptr<std::mutex> m_cvMutex;
};

#endif // EVENT_H
