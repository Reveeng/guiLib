#include "Timer.h"
#include <thread>
#include <chrono>

Timer::Timer():
    m_isSingleShot(false),
    m_time(1000)
{

}

Timer::~Timer()
{
    stop();
}


bool Timer::start()
{
    if (m_isSingleShot)
        m_timerThread = std::thread(&Timer::singleShotF, this);
    else
        m_timerThread = std::thread(&Timer::repeatedF, this);
    return true;
}

 bool Timer::start(uint32_t msec)
{
     if (m_timerThread.joinable())
         return false;
    m_time = msec;
    return start();
}

void Timer::stop()
{
    m_cancelCv.notify_one();
    if (m_timerThread.joinable())
        m_timerThread.join();
}

void Timer::setSingleShot(bool s)
{
    m_isSingleShot = s;
}

bool Timer::isSingleShot() const
{
    return m_isSingleShot;
}

void Timer::setTimerFunction(std::function<void ()> cb)
{
    m_callback = cb;
}

void Timer::repeatedF()
{
    std::cv_status st = std::cv_status::timeout;
    while (st == std::cv_status::timeout){
        std::unique_lock<std::mutex> g(m_mutex);
        st = m_cancelCv.wait_for(g, std::chrono::milliseconds(m_time));
        if (st == std::cv_status::timeout)
            m_callback();
    }
}

void Timer::singleShotF(){
    std::unique_lock<std::mutex> g(m_mutex);
    std::cv_status st = m_cancelCv.wait_for(g,std::chrono::milliseconds(m_time));
    if (st == std::cv_status::timeout)
        m_callback();
}
