#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <GObject.h>
#include <Buffer.h>

using Display::Buffer;
class Rectangle : public GObject
{
public:
    Rectangle(GObject *parent);
    Rectangle(uint32_t x, uint32_t y, uint32_t w, uint32_t h,GObject *parent = nullptr);

    ~Rectangle();

    void setFillBackground(bool f);
    bool fillBackground() const;

    void setBorderWidth(uint32_t w);
    uint32_t borderWidth() const;

protected:
    virtual void updateBuffer() override;
    uint32_t m_borderWidth;
    bool m_backgroundFill;

protected://callback
    void fillBackgroundChanged(bool);
    void borderWidthChanged(uint32_t);

private:
    void initFunctions();

    void fillBackground_();
    void fillBorders();

//    void fillBackgroundChangedCallback(bool f);
//    void fillBorders();
};

#endif // RECTANGLE_H
