#include "Rectangle.h"
#include <cstring>
#include <iostream>

using namespace std::placeholders;
using Display::Buffer;

Rectangle::Rectangle(GObject *parent):
    GObject(parent),
    m_borderWidth(0),
    m_backgroundFill(true)
{
    initFunctions();
    m_objectBuffer = new Buffer();
}

Rectangle::Rectangle(uint32_t x, uint32_t y, uint32_t w, uint32_t h,GObject *p):
    GObject(x,y,w,h,p),
    m_borderWidth(0),
    m_backgroundFill(true)
{
    initFunctions();
    m_objectBuffer = new Buffer(w,h);
}

Rectangle::~Rectangle()
{

}

void Rectangle::initFunctions()
{
    declare_setter_getter(m_backgroundFill);
    declare_setter_getter(m_borderWidth);
    bind_callback(m_backgroundFill,&Rectangle::fillBackgroundChanged);
    bind_callback(m_borderWidth, &Rectangle::borderWidthChanged);
}

void Rectangle::setFillBackground(bool f)
{
//    invokeSetter("m_backgroundFill",f);
    call_setter(m_backgroundFill,f);
}

bool Rectangle::fillBackground() const
{
    return invokeGetter<bool>("m_backgroundFill");
}

void Rectangle::updateBuffer()
{
    Buffer *b = dynamic_cast<Buffer*>(m_objectBuffer);
    b->setSizes(width(), height());
    fillBorders();
    fillBackground_();
    GObject::updateBuffer();
}

void Rectangle::fillBackgroundChanged(bool)
{
    updateBuffer();
    redraw();
}

void Rectangle::borderWidthChanged(uint32_t)
{
    updateBuffer();
    redraw();
}

void Rectangle::fillBackground_(){
    if (!m_backgroundFill){
        return;
    }
    Buffer *b = dynamic_cast<Buffer*>(m_objectBuffer);
    char * data = b->dataPtr();
    int h = b->height();
    int hBytes = h/8+1;
    for (int i = 1; i <= hBytes; ++i){
        if ((h - i*8) >= 0)
            std::memset(data,0xff,b->width());
        else{
            char bt = (0xff >> (i*8-h));
            std::memset(data,bt, b->width());
        }
        data += b->width();
    }
//    std::cout << "after fill background" << '\n';
//    b->draw();
}

void Rectangle::setBorderWidth(uint32_t w)
{
    call_setter(m_borderWidth,w);
}

uint32_t Rectangle::borderWidth() const
{
    return invokeGetter<uint32_t>("m_borderWidth");
}

void Rectangle::fillBorders()
{
    if (m_borderWidth == 0 || m_backgroundFill)
        return;
    Buffer *b = dynamic_cast<Buffer*>(m_objectBuffer);

    if (m_borderWidth >= b->height()/2){
        m_backgroundFill = true;
        return;
    }
    char *data = b->dataPtr();
    uint32_t h = b->height();
    uint32_t hBytes = h/8+1;
    uint32_t bottomBorderStartPos = b->height()-m_borderWidth;
    for (uint32_t i = 1; i <=hBytes; ++i){
        int d = h-i*8;
        char sideByte = ((d)>0) ? 0xff : (0xff >> (-d));
        std::memset(data,sideByte,m_borderWidth);
        std::memset(data+b->width()-m_borderWidth,sideByte,m_borderWidth);
        char fillerByte = 0x00;
        if (i == 1){
            fillerByte |= (0xff >> (8-m_borderWidth));
        }
        if (bottomBorderStartPos/8+1 <= i){
            int bottomOffset = i*8-bottomBorderStartPos-m_borderWidth;
            bottomOffset = bottomOffset < 0 ? 0 : bottomOffset;
            int topOffset = 8-(i*8-bottomBorderStartPos);
            topOffset = topOffset < 0 ? 0 : topOffset;
            char lofByte = (0xff << topOffset);
            char rofByte = (0xff >> bottomOffset);
            fillerByte |= lofByte&rofByte;
        }
        std::memset(data+m_borderWidth,fillerByte,b->width()-m_borderWidth*2);
        data += b->width();
    }
//    std::cout << "after fill border" << '\n';
//    b->draw();
}
