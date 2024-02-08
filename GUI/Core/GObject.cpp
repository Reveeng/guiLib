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
//    if (isVerticalBounded() && (al == VCenter || al == CenterIn))
//        return;
//    if (isHorizontalBounded() && (al == HCenter || al == CenterIn))
//        return;
    m_alignment = al;
    calculatePosition();
}

//void GObject::setTopAnchor(GObject *o, AnchorType t)
//{
//    if (!isCalledFromMainEventLoop()){
//        auto slf = std::bind(&GObject::setTopAnchor, this, _1, _2);
//        Event<GObject*,AnchorType> ev(slf,o,t);
//        m_objectEventLoop->pushEvent(ev);
//        return;
//    }
//    if (t == Right || t == Left)
//        return;
//    if (m_alignment == VCenter || m_alignment == CenterIn)
//        return;
//    if (m_parent != o && o->m_parent != m_parent)
//        return;
//    m_anchors[Top] = std::make_pair(o,t);
//}

//void GObject::setBottomAnchor(GObject *o, AnchorType t)
//{
//    if (!isCalledFromMainEventLoop()){
//        auto slf = std::bind(&GObject::setBottomAnchor, this, _1, _2);
//        Event<GObject*,AnchorType> ev(slf,o,t);
//        m_objectEventLoop->pushEvent(ev);
//        return;
//    }
//    if (t == Right || t == Left )
//        return;
//    if (m_alignment == VCenter || m_alignment == CenterIn)
//        return;
//    if (m_parent != o && o->m_parent != m_parent)
//        return;
//    m_anchors[Bottom] = std::make_pair(o,t);
//}

//void GObject::setRightAnchor(GObject *o, AnchorType t)
//{
//    if (!isCalledFromMainEventLoop()){
//        auto slf = std::bind(&GObject::setRightAnchor, this, _1, _2);
//        Event<GObject*,AnchorType> ev(slf,o,t);
//        m_objectEventLoop->pushEvent(ev);
//        return;
//    }
//    if (t == Top || t == Bottom)
//        return;
//    if (m_alignment == HCenter || m_alignment == CenterIn)
//        return;
//    if (m_parent != o && o->m_parent != m_parent)
//        return;
//    m_anchors[Right] = std::make_pair(o,t);
//}

//void GObject::setLeftAnchor(GObject *o, AnchorType t)
//{
//    if (!isCalledFromMainEventLoop()){
//        auto slf = std::bind(&GObject::setRightAnchor, this, _1, _2);
//        Event<GObject*,AnchorType> ev(slf,o,t);
//        m_objectEventLoop->pushEvent(ev);
//        return;
//    }
//    if (t == Top || t == Bottom)
//        return;
//    if (m_alignment == HCenter || m_alignment == CenterIn)
//        return;
//    if (m_parent != o && o->m_parent != m_parent)
//        return;
//    m_anchors[Right] = std::make_pair(o,t);
//}

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
//    calculateHorizontalPosition();
//    calculateVerticalPosition();
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

//void GObject::calculateVerticalPosition()
//{
//    AnchorPair top = m_anchors[Top];
//    AnchorPair bottom = m_anchors[Bottom];
//    uint32_t ny = y();
//    uint32_t nw = width();
//    if (m_parent == top.first){
//        ny = top.second == Top ? 0 : ny;
//    }
//    if ((m_parent != top.first) && top.first){
//        ny = top.second == Top ? top.first->y() : top.first->y()+top.first->height();
//    }
//    if ()

//}

//void GObject::calculateNewY(const AnchorPair &p)
//{
//    if (m_parent == p.first){

//    }
//}

//void GObject::calculateNewWidth(const AnchorPair &tp, const AnchorPair &bt)
//{

//}

//void GObject::calculateHorizontalPosition()
//{

//    AnchorPair right = m_anchors[Top];
//    AnchorPair left = m_anchors[Bottom];
//}

void GObject::setBuffer(Display::Abstraction::AbstractFrameBuffer *buf)
{
    m_objectBuffer = buf;
    draw();
}

//bool GObject::isVerticalBounded() const
//{
//    return m_anchors[Top].first || m_anchors[Bottom].first;
//}

//bool GObject::isHorizontalBounded() const
//{
//    return m_anchors[Right].first || m_anchors[Left].first;
//}
