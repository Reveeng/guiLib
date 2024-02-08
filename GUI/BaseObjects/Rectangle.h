#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <GObject.h>
#include <Buffers/MI12864/Buffer.h>

class Rectangle : public GObject
{
public:
    Rectangle(GObject *parent);
    Rectangle(uint32_t x, uint32_t y, uint32_t w, uint32_t h,GObject *parent = nullptr);

    ~Rectangle();

    void setFillBackground(bool f);
    bool fillBackground() const;

    void setBorderWidth(uint16_t w);
    uint16_t borderWidth() const;

protected:
    virtual void updateBuffer() override;

private:
    void _fillBackground();
    void fillBorders();
    uint16_t m_borderWidth;
    bool m_backgroundFill;
};

#endif // RECTANGLE_H
