#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include <Event.h>
#include <vector>


class EventQueue
{
public:
    EventQueue();
    void waitEvent();
    void breakWait();

    template <class T, typename std::enable_if_t<std::is_base_of_v<AbstractEvent,T>, bool> = true>
    void pushEvent(T &event){
        T *ev = new T(event);
        std::lock_guard<std::mutex> g(m_dataMutex);
        m_events.emplace_back(dynamic_cast<AbstractEvent*>(ev));
        breakWait();
    }

    void getEvents(std::vector<AbstractEvent*> &cont);

private:
    std::vector<AbstractEvent*> m_events;
    std::mutex m_dataMutex;
    int m_dropWaitReadFd;
    int m_dropWaitWriteFd;
};

#endif // EVENTQUEUE_H
