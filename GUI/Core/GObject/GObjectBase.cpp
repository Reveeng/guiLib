#include "GObjectBase.h"
#include <iostream>

using namespace std::placeholders;

GObjectBase::GObjectBase():
    GObjectRectangle(),
    m_visible(true)
{
}

GObjectBase::GObjectBase(uint32_t x, uint32_t y, uint32_t w, uint32_t h):
    GObjectRectangle(x,y,w,h),
    m_visible(true)
{

}

void GObjectBase::setX(uint32_t x)
{
    if (!isCalledFromMainEventLoop()){
        auto selfFunc = std::bind(&GObjectBase::setX, this, _1);
        Event<uint32_t> ev(selfFunc,x);
        m_objectEventLoop->pushEvent(ev);
        return;
    }
    GObjectRectangle::setX(x);
}

uint32_t GObjectBase::x() const
{
    if (!isCalledFromMainEventLoop()){
        auto selfFun = std::bind(&GObjectBase::x, this);
        WaitableEvent<uint32_t> ev(selfFun);
        m_objectEventLoop->pushEvent(ev);
        return ev.waitEventExecution();
    }
    return GObjectRectangle::x();
}

void GObjectBase::setY(uint32_t y)
{
    if (!isCalledFromMainEventLoop()){
        auto selfFunc = std::bind(&GObjectBase::setY, this,_1);
        Event<uint32_t> ev(selfFunc,y);
        m_objectEventLoop->pushEvent(ev);
        return;
    }
    GObjectRectangle::setY(y);
}

uint32_t GObjectBase::y() const
{
    if (!isCalledFromMainEventLoop()){
        auto selfFun = std::bind(&GObjectBase::y, this);
        WaitableEvent<uint32_t> ev(selfFun);
        m_objectEventLoop->pushEvent(ev);
        return ev.waitEventExecution();
    }
    return GObjectRectangle::y();
}

void GObjectBase::setPosition(uint32_t x, uint32_t y)
{
    if (!isCalledFromMainEventLoop()){
        auto selfFunc = std::bind(&GObjectBase::setPosition, this,_1,_2);
        Event<uint32_t, uint32_t> ev(selfFunc,x,y);
        m_objectEventLoop->pushEvent(ev);
        return;
    }
    GObjectRectangle::setPosition(x,y);
}

void GObjectBase::setWidth(uint32_t w)
{
    if (!isCalledFromMainEventLoop()){
        auto selfFunc = std::bind(&GObjectBase::setWidth, this,_1);
        Event<uint32_t> ev(selfFunc,w);
        m_objectEventLoop->pushEvent(ev);
        return;
    }
    GObjectRectangle::setWidth(w);
}

uint32_t GObjectBase::width() const
{
    if (!isCalledFromMainEventLoop()){
        auto selfFun = std::bind(&GObjectBase::width, this);
        WaitableEvent<uint32_t> ev(selfFun);
        m_objectEventLoop->pushEvent(ev);
        return ev.waitEventExecution();
    }
    return GObjectRectangle::width();
}

void GObjectBase::setHeight(uint32_t h)
{
    if (!isCalledFromMainEventLoop()){
        auto selfFunc = std::bind(&GObjectBase::setHeight, this,_1);
        Event<uint32_t> ev(selfFunc,h);
        m_objectEventLoop->pushEvent(ev);
        return;
    }
    GObjectRectangle::setHeight(h);
}

uint32_t GObjectBase::height() const
{
    if (!isCalledFromMainEventLoop()){
        auto selfFun = std::bind(&GObjectBase::height, this);
        WaitableEvent<uint32_t> ev(selfFun);
        m_objectEventLoop->pushEvent(ev);
        return ev.waitEventExecution();
    }
    return GObjectRectangle::height();
}

void GObjectBase::setSizes(uint32_t w, uint32_t h)
{
    if (!isCalledFromMainEventLoop()){
        auto selfFunc = std::bind(&GObjectBase::setSizes, this,_1,_2);
        Event<uint32_t, uint32_t> ev(selfFunc,w,h);
        m_objectEventLoop->pushEvent(ev);
        return;
    }
    GObjectRectangle::setSizes(w,h);
}

void GObjectBase::setVisible(bool v)
{
    if (!isCalledFromMainEventLoop()){
        auto self = std::bind(&GObjectBase::setVisible, this,_1);
        Event<bool> ev(self,v);
        m_objectEventLoop->pushEvent(ev);
        return;
    }
    m_visible = v;
    afterVisibleChanged();
}

bool GObjectBase::visible() const
{
    if (!isCalledFromMainEventLoop()){
        auto self = std::bind(&GObjectBase::visible, this);
        WaitableEvent<bool> ev(self);
        m_objectEventLoop->pushEvent(ev);
        return ev.waitEventExecution();
    }
    return m_visible;
}

bool GObjectBase::isCalledFromMainEventLoop() const
{
    if (!m_objectEventLoop)
        return true;
    return m_objectEventLoop->eventLoopThredId() == std::this_thread::get_id();
}

void GObjectBase::setObjectEventLoop(EventLoop *loop)
{
    m_objectEventLoop = loop;
}
