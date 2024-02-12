#ifndef GTIMER_H
#define GTIMER_H

#include <Event.h>
#include <EventLoop.h>
#include <thread>
#include <condition_variable>


class GTimer{
public:
    GTimer(uint32_t timerId = 0);
    GTimer(EventLoop *evL, uint32_t timerId = 0);
    ~GTimer();

    bool start();
    bool start(uint32_t msec);
    void stop();

    void setSingleShot(bool sh);
    bool isSingleShot() const;

    void setDetached(bool d);
    bool isDetached() const;

    uint32_t id() const;

    void setTimerEventLoop(EventLoop *evL);

    void setTimeoutFunction(std::function<void()> f);

protected:
    void startDetached();

    void singleShotF();
    void repeatedF();

private:
    bool m_isSingleShot;
    bool m_isDetached;
    uint32_t m_time;
    Event<> * m_ev;
    EventLoop *m_eventLoop;

    std::thread m_timerThread;
    std::condition_variable m_cancelCv;
    std::mutex m_mutex;
    uint32_t m_id;
};

#endif // GTIMER_H
