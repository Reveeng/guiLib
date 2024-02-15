#include <GObject.h>
#include <MainEventLoop.h>
#include <GObjectRectangle.h>
#include <algorithm>
#include <iostream>

using namespace std::placeholders;

GObject::GObject(GObject *p):
    GObjectBase(),
    m_objectBuffer(nullptr),
    m_parent(p),
    m_alignment(NoAlign),
    m_anchors(this)
{
    if (!m_parent)
        return;
    m_parent->m_children.push_back(this);
//    m_objectEventLoop = m_parent->m_objectEventLoop;
    m_anchors.setParent(m_parent);
}

GObject::GObject(uint32_t x, uint32_t y, uint32_t w, uint32_t h,GObject *p):
    GObjectBase(x,y,w,h),
    m_parent(p),
    m_alignment(NoAlign),
    m_anchors(this)
{
    if (!m_parent)
        return;
    m_parent->m_children.push_back(this);
    m_objectEventLoop = m_parent->m_objectEventLoop;
    m_anchors.setParent(m_parent);
}

GObject::~GObject()
{
    for (auto timer : m_timers){
        timer->stop();
        delete timer;
    }
    for (auto child : m_children){
        child->m_parent = nullptr;
        delete child;
    }
    if (m_parent){
        auto pred = [this](GObject *o){return this == o;};
        auto begIter = m_parent->m_children.begin();
        auto endIter = m_parent->m_children.end();
        auto iter = std::find_if(begIter, endIter,pred);
        if (iter != endIter)
            m_parent->m_children.erase(iter);
    }

    delete m_objectBuffer;
}

GObject *GObject::parent() const
{
    return m_parent;
}

void GObject::setParent(GObject *p)
{
    if (!p)
        return;
    m_parent = p;
    m_parent->m_children.push_back(this);
    m_objectEventLoop = m_parent->m_objectEventLoop;
}

const std::vector<GObject *> &GObject::children() const
{
    return m_children;
}

void GObject::setAlignment(Alignment al)
{
    if (!isCalledFromMainEventLoop()){
        auto slf = std::bind(&GObject::setAlignment, this,_1);
        Event<GObject::Alignment> ev(slf, al);
        m_objectEventLoop->pushEvent(ev);
        return;
    }
    m_alignment = al;
    calculatePosition();
    redraw();
}

GTimer *GObject::getTimer()
{
    GTimer * timer = new GTimer(m_objectEventLoop,m_timers.size());
    m_timers.push_back(timer);
    return timer;
}

uint32_t GObject::startTimer(std::function<void ()> f, uint32_t time, bool isSingleShot)
{
    GTimer *timer = new GTimer(m_objectEventLoop, m_timerIdGen);
    timer->setSingleShot(isSingleShot);
    timer->setDetached(true);
    if (isSingleShot){
        auto rebindF = [f, timer](){f();delete timer;};
        auto rb = std::bind(rebindF);
        timer->setTimeoutFunction(rb);
    }else{
        m_timers.push_back(timer);
        timer->setTimeoutFunction(f);
    }
    timer->start(time);
    m_timerIdGen += 1;
    return isSingleShot ? 0 : timer->id();
}

void GObject::stopTimer(uint32_t id)
{
    auto pred = [id](GTimer* t){return t->id() == id;};
    auto iter = std::find_if(m_timers.begin(), m_timers.end(), pred);
    if (iter == m_timers.end())
        return;
    (*iter)->stop();
    GTimer *t = *iter;
    m_timers.erase(iter);
    delete t;
}

void GObject::updateBuffer()
{
    for (auto child : m_children){
        child->updateBuffer();
        m_objectBuffer->mergeData(child->m_objectBuffer, child->x(), child->y());
    }
}

void GObject::redraw()
{
    if (!visible() || !m_parent)
        return;
    Rect pos = position();
    Rect ppos = previousPosition();
    m_parent->m_objectBuffer->clearRectangle(ppos.x,ppos.y, ppos.w, ppos.h);
    m_parent->m_objectBuffer->mergeData(m_objectBuffer,pos.x, pos.y);
    m_parent->redraw();
}

void GObject::clear(){
    if (!m_parent)
        return;
    auto pos = position();
    m_parent->m_objectBuffer->clearRectangle(pos.x, pos.y, pos.w,pos.h);
    m_parent->redraw();
}

void GObject::afterObjectPositionChanged()
{
    for (auto anchored : m_anchoredObject)
        anchored->calculatePosition();
    redraw();
}

void GObject::afterObjectSizesChanged(){
    updateBuffer();
    for (auto child : m_children)
        child->calculatePosition();
    for (auto anchored : m_anchoredObject)
        anchored->calculatePosition();
    calculatePosition();
    redraw();
}

void GObject::afterVisibleChanged(){
    if (visible()){
        redraw();
    }else{
        clear();
    }
}

void GObject::calculatePosition()
{
    if (m_alignment != NoAlign){
        calculatePositionAlignBased();
        return;
    }
    m_anchors.calculatePosition();
}

void GObject::removedAnchoredObject(GObject *o)
{
    auto pred = [o](GObjectRectangle *r){return o == r;};
    auto iter = std::find_if(m_anchoredObject.begin(), m_anchoredObject.end(), pred);
    if (iter == m_anchoredObject.end())
        return;
    m_anchoredObject.erase(iter);
}

void GObject::calculatePositionAlignBased()
{
    auto parPos = m_parent->position();
    int hcx = parPos.w/2-width()/2;
    hcx = hcx < 0 ? 0 : hcx;
    int vcy = parPos.h/2-height()/2;
    vcy = vcy < 0 ? 0 : vcy;
    switch(m_alignment){
        case NoAlign:return;
        case VCenter:
            setY(vcy);
            break;
        case HCenter:
            setX(hcx);
            break;
        case CenterIn:
            setPosition(hcx,vcy);
            break;
    }
}

void GObject::setBuffer(Display::Abstraction::AbstractFrameBuffer *buf)
{
    m_objectBuffer = buf;
    redraw();
}
