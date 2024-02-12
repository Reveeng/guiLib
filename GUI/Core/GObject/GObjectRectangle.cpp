#include "GObjectRectangle.h"

bool operator==(const Rect &lhs, const Rect &rhs){
    return lhs.x == rhs.x &&
           lhs.y == rhs.y &&
           lhs.w == rhs.w &&
           lhs.h == rhs.h;
}


GObjectRectangle::GObjectRectangle():
    m_currentPosition({0,0,0,0}),
    m_previousPosition({0,0,0,0})
{

}

GObjectRectangle::GObjectRectangle(uint32_t x, uint32_t y,
                                   uint32_t w, uint32_t h):
    m_currentPosition({x,y,w,h}),
    m_previousPosition(m_currentPosition)
{

}

void GObjectRectangle::setX(uint32_t x)
{
    if (m_currentPosition.x == x)
        return;
    savePosition();
    m_currentPosition.x = x;
    afterObjectPositionChanged();
}

uint32_t GObjectRectangle::x() const
{
    return m_currentPosition.x;
}

void GObjectRectangle::setY(uint32_t y)
{
    if (m_currentPosition.y == y)
        return;
    savePosition();
    m_currentPosition.y = y;
    afterObjectPositionChanged();
}

uint32_t GObjectRectangle::y() const
{
    return m_currentPosition.y;
}

void GObjectRectangle::setPosition(uint32_t x, uint32_t y)
{
    if (m_currentPosition.x == x && m_currentPosition.y == y)
        return;
    savePosition();
    m_currentPosition.x = x;
    m_currentPosition.y = y;
    afterObjectPositionChanged();
}

void GObjectRectangle::setWidth(uint32_t w)
{
    if (m_currentPosition.w == w)
        return;
    savePosition();
    m_currentPosition.w = w;
    afterObjectSizesChanged();
}

uint32_t GObjectRectangle::width() const
{
    return m_currentPosition.w;
}

void GObjectRectangle::setHeight(uint32_t h)
{
    if (m_currentPosition.h == h)
        return;
    savePosition();
    m_currentPosition.h = h;
    afterObjectSizesChanged();
}

uint32_t GObjectRectangle::height() const
{
    return m_currentPosition.h;
}

void GObjectRectangle::setSizes(uint32_t w, uint32_t h)
{
    if (m_currentPosition.w == w && m_currentPosition.h == h)
        return;
    savePosition();
    m_currentPosition.w = w;
    m_currentPosition.h = h;
    afterObjectSizesChanged();
}

void GObjectRectangle::savePosition()
{
    m_previousPosition = m_currentPosition;
}

bool GObjectRectangle::isPositionChanged()
{
    return !(m_currentPosition == m_previousPosition);
}

const Rect &GObjectRectangle::position() const
{
    return m_currentPosition;
}

const Rect &GObjectRectangle::previousPosition() const
{
    return m_previousPosition;
}
