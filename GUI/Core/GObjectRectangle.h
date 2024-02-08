#ifndef GOBJECTRECTANGLE_H
#define GOBJECTRECTANGLE_H

#include <inttypes.h>

typedef struct r{
    uint32_t x;
    uint32_t y;
    uint32_t w;
    uint32_t h;
} Rect;

class GObjectRectangle
{
public:
    GObjectRectangle();
    GObjectRectangle(uint32_t x, uint32_t y, uint32_t w, uint32_t h);

    void setX(uint32_t x);
    uint32_t x() const;

    void setY(uint32_t y);
    uint32_t y() const;

    void setPosition(uint32_t x, uint32_t y);

    void setWidth(uint32_t w);
    uint32_t width() const;

    void setHeight(uint32_t h);
    uint32_t height() const;

    void setSizes(uint32_t w, uint32_t h);

protected:
    void savePosition();
    bool isPositionChanged();

    const Rect &position() const;
    const Rect &previousPosition() const;

    virtual void afterObjectPositionChanged() = 0;
    virtual void afterObjectSizesChanged() = 0;

private:
    Rect m_currentPosition;
    Rect m_previousPosition;
};

#endif // GOBJECTRECTANGLE_H
