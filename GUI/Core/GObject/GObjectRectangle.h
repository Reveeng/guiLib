#ifndef GOBJECTRECTANGLE_H
#define GOBJECTRECTANGLE_H

#include <inttypes.h>
#include <AbstractClass.h>

typedef struct r{
    uint32_t x;
    uint32_t y;
    uint32_t w;
    uint32_t h;
} Rect;

class GObjectBase : public AbstractClass
{
public:
    GObjectBase(AbstractClass *parent = nullptr);
    GObjectBase(const Rect &r, AbstractClass *parent = nullptr);

    virtual ~GObjectBase();

    void setX(uint32_t x);
    uint32_t x() const;

    void setY(uint32_t y);
    uint32_t y() const;

    void setWidth(uint32_t w);
    uint32_t width() const;

    void setHeight(uint32_t h);
    uint32_t height() const;

    void setVisible(bool v);
    bool visible() const;

    void setSizes(uint32_t w, uint32_t h);

    void setPosition(uint32_t x, uint32_t y);

protected:
    bool isPositionChanged();

    const Rect &position() const;
    const Rect &previousPosition() const;


private:
    void initSettersAndGetters();
    Rect m_currentPosition;
    bool m_visible;
};

#endif // GOBJECTRECTANGLE_H
