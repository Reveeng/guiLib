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
    m_objectBuffer = new Buffer();
}

Rectangle::Rectangle(uint32_t x, uint32_t y, uint32_t w, uint32_t h,GObject *p):
    GObject(x,y,w,h,p),
    m_borderWidth(0),
    m_backgroundFill(true)
{
    m_objectBuffer = new Buffer(w,h);
}

Rectangle::~Rectangle()
{

}

void Rectangle::setFillBackground(bool f)
{
    if (!isCalledFromMainEventLoop()){
        auto slf = std::bind(&Rectangle::setFillBackground, this,_1);
        Event<bool> ev(slf,f);
        m_objectEventLoop->pushEvent(ev);
        return;
    }
    if (m_backgroundFill == f)
        return;
    m_backgroundFill = f;
    updateBuffer();
    draw();
}

bool Rectangle::fillBackground() const
{
    if (!isCalledFromMainEventLoop()){
        auto slf = std::bind(&Rectangle::fillBackground, this);
        WaitableEvent<bool> ev(slf);
        m_objectEventLoop->pushEvent(ev);
        return ev.waitEventExecution();
    }
    return m_backgroundFill;
}

void Rectangle::updateBuffer()
{
    Buffer *b = dynamic_cast<Buffer*>(m_objectBuffer);
    b->setSizes(width(), height());
    fillBorders();
    _fillBackground();
}

void Rectangle::_fillBackground(){
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
}

void Rectangle::setBorderWidth(uint16_t w)
{
    if (!isCalledFromMainEventLoop()){
        auto slf = std::bind(&Rectangle::setBorderWidth, this,_1);
        Event<uint16_t> ev(slf,w);
        m_objectEventLoop->pushEvent(ev);
        return;
    }
    if (m_borderWidth == w)
        return;
    m_borderWidth = w;
    updateBuffer();
    draw();
}

uint16_t Rectangle::borderWidth() const
{
    if (!isCalledFromMainEventLoop()){
        auto slf = std::bind(&Rectangle::borderWidth, this);
        WaitableEvent<uint16_t> ev(slf);
        m_objectEventLoop->pushEvent(ev);
        return ev.waitEventExecution();
    }
    return m_borderWidth;
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
}
