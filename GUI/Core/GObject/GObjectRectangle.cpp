#include "GObjectRectangle.h"

bool operator==(const Rect &lhs, const Rect &rhs){
    return lhs.x == rhs.x &&
           lhs.y == rhs.y &&
           lhs.w == rhs.w &&
           lhs.h == rhs.h;
}
bool operator!=(const Rect &lhs, const Rect &rhs){
    return !(lhs == rhs);
}


GObjectBase::GObjectBase(AbstractClass *parent):
    AbstractClass(parent),
    m_pos({0,0,0,0}),
    m_visible(true)
{
    initSettersAndGetters();
}

GObjectBase::GObjectBase(const Rect &r, AbstractClass *parent):
    AbstractClass(parent),
    m_pos(r),
    m_visible(true)
{
    initSettersAndGetters();
}

GObjectBase::~GObjectBase()
{
}

void GObjectBase::initSettersAndGetters()
{
    createObjectSetter("rect", m_pos);
    createObjectGetter("rect", m_pos);
    createObjectSetter("visible",m_visible);
    createObjectGetter("visible",m_visible);
    connect("rect", &GObjectBase::positionChangedCallback, this);

    createObjectSetter("deleted");
}

void GObjectBase::setX(uint32_t x)
{
    Rect nr = rectangle();
    nr.x = x;
    invokeSetter("rect", nr);
}

uint32_t GObjectBase::x() const
{
    Rect r = invokeGetter<Rect>("rect");
    return r.x;
}

void GObjectBase::setY(uint32_t y)
{
    Rect nr = m_pos;
    nr.y = y;
    invokeSetter("rect", nr);
}

uint32_t GObjectBase::y() const
{
    Rect r = invokeGetter<Rect>("rect");
    return r.y;
}

void GObjectBase::setPosition(uint32_t x, uint32_t y)
{
    Rect nr = rectangle();
    nr.x = x;
    nr.y = y;
    invokeSetter("rect", nr);
}

void GObjectBase::setRectangle(uint32_t x, uint32_t y, uint32_t w, uint32_t h)
{
    invokeSetter("rect",Rect{x,y,w,h});
}

Rect GObjectBase::rectangle() const
{
    return invokeGetter<Rect>("rect");
}

void GObjectBase::setWidth(uint32_t w)
{
    Rect nr = rectangle();
    nr.w = w;
    invokeSetter("rect",nr);
}

uint32_t GObjectBase::width() const
{
    Rect r = invokeGetter<Rect>("rect");
    return r.w;
}

void GObjectBase::setHeight(uint32_t h)
{
    Rect nr = rectangle();
    nr.h = h;
    invokeSetter("rect", nr);
}

uint32_t GObjectBase::height() const
{
    Rect r = invokeGetter<Rect>("rect");
    return r.h;
}

void GObjectBase::setVisible(bool v)
{
    invokeSetter("visible", v);
}

bool GObjectBase::visible() const
{
    return invokeGetter<bool>("visible");
}

void GObjectBase::setSizes(uint32_t w, uint32_t h)
{

    Rect nr = rectangle();
    nr.w = w;
    nr.h = h;
    invokeSetter("rect",nr);
}
