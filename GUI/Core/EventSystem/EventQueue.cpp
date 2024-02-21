#include "EventQueue.h"
#include <unistd.h>
#include <sys/select.h>
#include <iostream>

EventQueue::EventQueue()
{
}

void EventQueue::waitEvent()
{
    std::unique_lock lk(m_cvMutex);
    m_cv.wait_for(lk,std::chrono::milliseconds(100));
    lk.unlock();
}

void EventQueue::breakWait()
{
    m_cv.notify_one();
}

void EventQueue::getEvents(std::vector<AbstractEvent *> &cont)
{
    std::lock_guard<std::mutex> g(m_dataMutex);
    m_events.swap(cont);
}

std::size_t EventQueue::size()
{
    std::lock_guard<std::mutex> g(m_dataMutex);
    return m_events.size();
}


