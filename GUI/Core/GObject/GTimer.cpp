#include "GTimer.h"
#include <thread>
#include <chrono>

GTimer::GTimer(uint32_t id):
    AbstractClass(),
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
    m_objectEventLoop->start();
    if (m_isDetached){
        auto f = std::bind(&GTimer::__start, this);
        Event<> e(f);
        m_objectEventLoop->pushEvent(e);
        return true;
    }
    __start();
    return true;

}

 bool GTimer::start(uint32_t msec)
{
    m_time = msec;
    return start();
}

void GTimer::stop()
{
    m_cancelCv.notify_one();
    m_objectEventLoop->stop();
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

void GTimer::repeatedF()
{
    std::cv_status st = std::cv_status::timeout;
    while (st == std::cv_status::timeout){
        std::unique_lock<std::mutex> g(m_mutex);
        st = m_cancelCv.wait_for(g, std::chrono::milliseconds(m_time));
        if (st == std::cv_status::timeout)
            invokeSignal<>("timeout");
    }
}

void GTimer::__start()
{
    if (m_isSingleShot)
        singleShotF();
    else
        repeatedF();
}

void GTimer::singleShotF(){
    std::unique_lock<std::mutex> g(m_mutex);
    std::cv_status st = m_cancelCv.wait_for(g,std::chrono::milliseconds(m_time));
    if (st == std::cv_status::timeout)
        invokeSignal<>("timeout");
    deleteLater();
}
