#include "GObjectRectangle.h"

bool operator==(const Rect &lhs, const Rect &rhs){
    return lhs.x == rhs.x &&
           lhs.y == rhs.y &&
           lhs.w == rhs.w &&
           lhs.h == rhs.h;
}


GObjectBase::GObjectBase(AbstractClass *parent):
    AbstractClass(parent),
    m_currentPosition({0,0,0,0})
{
    initSettersAndGetters();
}

GObjectBase::GObjectBase(const Rect &r, AbstractClass *parent):
    AbstractClass(parent),
    m_currentPosition(r)
{
    initSettersAndGetters();
}

GObjectBase::~GObjectBase()
{

}

void GObjectBase::initSettersAndGetters()
{
    createObjectSetter("x", m_currentPosition.x);
    createObjectSetter("y", m_currentPosition.y);
    createObjectSetter("w", m_currentPosition.w);
    createObjectSetter("h", m_currentPosition.h);
    createObjectSetter("v", m_visible);
    createObjectSetter("pos", m_currentPosition.x, m_currentPosition.y);
    createObjectSetter("sizes", m_currentPosition.w, m_currentPosition.h);

    createObjectGetter("x",m_currentPosition.x);
    createObjectGetter("y",m_currentPosition.y);
    createObjectGetter("w",m_currentPosition.w);
    createObjectGetter("h",m_currentPosition.h);
    createObjectGetter("v", m_visible);
}

void GObjectBase::setX(uint32_t x)
{
    invokeSetter("x", x);
}

uint32_t GObjectBase::x() const
{
    return invokeGetter<uint32_t>("x");
}

void GObjectBase::setY(uint32_t y)
{
    invokeSetter("y", y);
}

uint32_t GObjectBase::y() const
{
    return invokeGetter<uint32_t>("y");
}

void GObjectBase::setPosition(uint32_t x, uint32_t y)
{
    invokeSetter("pos",x,y);
}

void GObjectBase::setWidth(uint32_t w)
{
    invokeSetter("w",w);
}

uint32_t GObjectBase::width() const
{
    return invokeGetter<uint32_t>("w");
}

void GObjectBase::setHeight(uint32_t h)
{
    invokeSetter("h",h);
}

uint32_t GObjectBase::height() const
{
    return invokeGetter<uint32_t>("h");
}

void GObjectBase::setVisible(bool v)
{
    invokeSetter("v", v);
}

bool GObjectBase::visible() const
{
    return invokeGetter<bool>("v");
}

void GObjectBase::setSizes(uint32_t w, uint32_t h)
{
    invokeSetter("sizes",w,h);
}

//void GObjectBase::savePosition()
//{
//    m_previousPosition = m_currentPosition;
//}

bool GObjectBase::isPositionChanged()
{
//    return !(m_currentPosition == m_previousPosition);
}

const Rect &GObjectBase::position() const
{
    return m_currentPosition;
}

const Rect &GObjectBase::previousPosition() const
{
//    return m_previousPosition;
}
