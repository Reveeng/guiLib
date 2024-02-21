#include "EventLoop.h"

EventLoop::EventLoop():
    m_stopFlag(false)
{

}

EventLoop::~EventLoop()
{
    stop();
}

void EventLoop::start()
{
    m_thread = std::thread(&EventLoop::loop, this);
}

void EventLoop::stop()
{
    m_stopFlag.store(true);
    breakWait();
    m_thread.join();
}

std::thread::id EventLoop::eventLoopThredId()
{
    return m_thread.get_id();
}

void EventLoop::loop()
{
    while (!m_stopFlag.load()){
        waitEvent();
        if (size() == 0)
            continue;
        std::vector<AbstractEvent*> events;
        getEvents(events);
        for (auto ev : events){
            ev->executeCallback();
        }
        clearQueue(events);
    }
}

void EventLoop::clearQueue(std::vector<AbstractEvent *> &ev)
{
    while (ev.size() != 0){
        delete ev.back();
        ev.pop_back();
    }
}
