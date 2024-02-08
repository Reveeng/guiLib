#include <GObject.h>
#include <MainEventLoop.h>
#include <GObjectBase.h>
#include <algorithm>
#include <iostream>

using namespace std::placeholders;

using AnchorPair = std::pair<GObject*, GObject::AnchorType>;

GObject::GObject(GObject *p):
    GObjectBase(),
    m_objectBuffer(nullptr),
    m_parent(p),
    m_alignment(NoAlign)
{
    if (!m_parent)
        return;
    m_parent->m_children.push_back(this);
    m_objectEventLoop = m_parent->m_objectEventLoop;
}

GObject::GObject(uint32_t x, uint32_t y, uint32_t w, uint32_t h,GObject *p):
    GObjectBase(x,y,w,h),
    m_parent(p),
    m_alignment(NoAlign)
{
    if (!m_parent)
        return;
    m_parent->m_children.push_back(this);
    m_objectEventLoop = m_parent->m_objectEventLoop;
}

GObject::~GObject()
{
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
}

void GObject::draw(bool force)
{
    if(!visible() || !m_parent)
        return;
    if (isPositionChanged() || force){
        auto prevPos = previousPosition();
        m_parent->m_objectBuffer->clearRectangle(prevPos.x,prevPos.y,
                                                 prevPos.w,prevPos.h);
        m_parent->updateBuffer();
    }

    m_parent->m_objectBuffer->mergeData(m_objectBuffer, x(),y());
    m_parent->draw(true);
}

void GObject::clear(){
    if (!m_parent)
        return;
    auto pos = position();
    m_parent->m_objectBuffer->clearRectangle(pos.x, pos.y, pos.w,pos.h);
    m_parent->draw();
}

void GObject::afterObjectPositionChanged()
{
    draw();
}

void GObject::afterObjectSizesChanged(){
    updateBuffer();
    for (auto child : m_children)
        child->calculatePosition();
    draw();
}

void GObject::afterVisibleChanged(){
    if (visible()){
        draw();
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
    draw();
}
