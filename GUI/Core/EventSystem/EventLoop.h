#ifndef EVENTLOOP_H
#define EVENTLOOP_H

#include <thread>
#include <mutex>
#include <atomic>
#include <EventQueue.h>

class EventLoop : public EventQueue
{
public:
    EventLoop();
    ~EventLoop();

    void start();
    void stop();

    std::thread::id eventLoopThredId();

private:
    void loop();
    void clearQueue(std::vector<AbstractEvent *> &ev);

    std::atomic<bool> m_stopFlag;
    std::mutex m_queueMutex;
    std::thread m_thread;
};

#endif // EVENTLOOP_H
