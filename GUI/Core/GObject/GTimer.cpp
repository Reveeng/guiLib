#include "GTimer.h"
#include <thread>
#include <chrono>

GTimer::GTimer(AbstractClass *parent,uint32_t id):
    AbstractClass(parent),
    m_isSingleShot(false),
    m_isDetached(false),
    m_time(1000),
    m_id(id)
{
    createObjectSetter("timeout");
}

GTimer::~GTimer()
{
    stop();
}


bool GTimer::start()
{
    if (m_timerThread.joinable())
        return false;

    if (m_isDetached){
        startDetached();
        return true;
    }
    if (m_isSingleShot)
        singleShotF();
    else
        repeatedF();

    return true;

}

 bool GTimer::start(uint32_t msec)
{
     if (m_timerThread.joinable())
         return false;
    m_time = msec;
    return start();
}

void GTimer::stop()
{
    m_cancelCv.notify_one();
    if (m_timerThread.joinable())
        m_timerThread.join();
}

void GTimer::setSingleShot(bool s)
{
    m_isSingleShot = s;
}

bool GTimer::isSingleShot() const
{
    return m_isSingleShot;
}

void GTimer::setDetached(bool d)
{
    m_isDetached = d;
}

bool GTimer::isDetached() const
{
    return m_isDetached;
}

uint32_t GTimer::id() const{
    return m_id;
}
void GTimer::startDetached()
{
    if (m_isSingleShot)
        m_timerThread = std::thread(&GTimer::singleShotF, this);
    else
        m_timerThread = std::thread(&GTimer::repeatedF, this);
}

void GTimer::repeatedF()
{
    std::cv_status st = std::cv_status::timeout;
    while (st == std::cv_status::timeout){
        std::unique_lock<std::mutex> g(m_mutex);
        st = m_cancelCv.wait_for(g, std::chrono::milliseconds(m_time));
        if (st == std::cv_status::timeout)
            invokeSetter("timeout");
    }
}

void GTimer::singleShotF(){
    std::unique_lock<std::mutex> g(m_mutex);
    std::cv_status st = m_cancelCv.wait_for(g,std::chrono::milliseconds(m_time));
    if (st == std::cv_status::timeout)
        invokeSetter("timeout");
}
