#include <GObject.h>
#include <MainEventLoop.h>
#include <GObjectRectangle.h>
#include <algorithm>
#include <iostream>

using namespace std::placeholders;

GObject::GObject(GObject *p):
    GObjectBase(p),
    m_objectBuffer(nullptr),
    m_parent(p),
    m_alignment(NoAlign),
    m_inverse(false),
    m_anchors(this)
{
    declare_setter_getter(m_alignment);
    declare_setter_getter(m_inverse);
    bind_callback(m_alignment,&GObject::alignmentChanged);
    connect("aboutToDelete", &GObject::onDeleteCallback, this);
    bind_callback(m_inverse, &GObject::inverseChanged);
    m_prevPos = rectangle();

    if (!m_parent)
        return;
    m_parent->m_children.push_back(this);
    m_anchors.setParent(m_parent);
}

GObject::GObject(uint32_t x, uint32_t y, uint32_t w, uint32_t h,GObject *p):
    GObjectBase({x,y,w,h}, p),
    m_parent(p),
    m_alignment(NoAlign),
    m_inverse(false),
    m_anchors(this),
    m_prevPos({x,y,w,h})
{
    declare_setter_getter(m_alignment);
    declare_setter_getter(m_inverse);
    bind_callback(m_alignment,&GObject::alignmentChanged);
    connect("aboutToDelete", &GObject::onDeleteCallback, this);
    bind_callback(m_inverse, &GObject::inverseChanged);
    if (!m_parent)
        return;
    m_parent->m_children.push_back(this);
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
    call_setter(m_alignment, static_cast<int>(al));
}

GObject::Alignment GObject::alignment(){
    return static_cast<Alignment>(call_getter(m_alignment));
}

void GObject::setInversion(bool inv)
{
    call_setter(m_inverse, inv);
}

bool GObject::inversion() const
{
    return invokeGetter<bool>("m_inversion");
}

const AbstractFrameBuffer *GObject::buffer()
{
    return m_objectBuffer;
}

void GObject::setAnchor(AnchorType t1, GObject *ref, AnchorType t2, uint32_t offset)
{
    if (ref != m_parent &&ref->parent() != m_parent){
        std::cout << "Try to connect unconnectable objects";
        return;
    }
    GObjectBase *b = dynamic_cast<GObjectBase*>(ref);
    switch(t1){
        break; case AnchorType::Top: m_anchors.setTopAnchor(t2,b,offset);
        break; case AnchorType::Bottom: m_anchors.setBottomAnchor(t2,b,offset);
        break; case AnchorType::Right: m_anchors.setRightAnchor(t2,b,offset);
        break; case AnchorType::Left: m_anchors.setLeftAnchor(t2,b,offset);
        break; default: return;
    }
}


//GTimer *GObject::getTimer()
//{
//    GTimer * timer = new GTimer(,m_timers.size());
//    m_timers.push_back(timer);
//    return timer;
//}

uint32_t GObject::startTimer(std::function<void ()> f, uint32_t time, bool isSingleShot)
{
    GTimer *timer = new GTimer(m_timerIdGen);
    timer->setSingleShot(isSingleShot);
    timer->setDetached(true);
    if (isSingleShot){
        GObject::connect(timer,"timeout", f);
    }else{
        GObject::connect(timer, "timeout", f);
        m_timers.push_back(timer);
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
        if (child->visible())
            m_objectBuffer->mergeData(child->m_objectBuffer, child->x(), child->y());
        else
            m_objectBuffer->clearRectangle(child->x(), child->y(), child->width(), child->height());
    }
}

void GObject::redraw()
{
    if (!visible() || !m_parent)
        return;
    if (!m_parent->m_objectBuffer)
        return;
    Rect pos = rectangle();
    if (pos != m_prevPos)
        m_parent->m_objectBuffer->clearRectangle(m_prevPos.x,m_prevPos.y, m_prevPos.w, m_prevPos.h);
    m_parent->m_objectBuffer->mergeData(m_objectBuffer,pos.x, pos.y);
    m_parent->redraw();
}

void GObject::clear(){
    if (!m_parent)
        return;
    auto pos = rectangle();
    m_parent->m_objectBuffer->clearRectangle(pos.x, pos.y, pos.w,pos.h);
    m_parent->redraw();
}

void GObject::visibleChangedCallback(bool v){
    if (v){
        redraw();
    }else{
        clear();
    }
}

void GObject::onDeleteCallback(AbstractClass *o)
{
    (void)o;
    if (m_parent){
        m_parent->removeChild(this);
    }
    clear();
}

void GObject::inverseChanged(bool isinv)
{
    m_objectBuffer->setInverse(isinv);
    clear();
    redraw();
}

bool GObject::isPositionChanged(Rect &rect)
{
    return rect.x != m_prevPos.x || rect.y != m_prevPos.y;
}

bool GObject::isSizesChanged(Rect &rect)
{
    return rect.w != m_prevPos.w || rect.h != m_prevPos.h;
}

void GObject::calculatePosition()
{
    if (m_alignment != NoAlign){
        calculatePositionAlignBased();
    }
    if (m_anchors.hasAnchor())
        m_anchors.calculatePosition();
}

void GObject::removeChild(GObject *obj)
{
    auto pred = [obj](GObject *o){return obj == o;};

    m_children.erase(std::remove_if(m_children.begin(), m_children.end(), pred));
}

void GObject::calculatePositionAlignBased()
{
    Rect parPos = m_parent->rectangle();
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

void GObject::positionChangedCallback(Rect newR)
{

    bool sCh = isSizesChanged(newR);
    bool posCh = isPositionChanged(newR);
    if (sCh || posCh)
    {
        m_anchoredObjects.calculatePositions();
    }
    if (sCh){
        calculatePosition();
        m_children.calculatePositions();
    }
    updateBuffer();

    redraw();
    m_prevPos = newR;
}

void GObject::alignmentChanged(int)
{
    calculatePosition();
    redraw();
}

void GObjectContainer::calculatePositions()
{
    for (auto ref : *this){
        ref->calculatePosition();
    }
}

void GObjectContainer::print_data()
{

}
