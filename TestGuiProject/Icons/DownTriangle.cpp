#include "DownTriangle.h"
#include <Buffer.h>

static char triangle[] = {0x1,0x3,0x7,0xf,0x1f,0xf, 0x7,0x3,0x1};

DownTriangle::DownTriangle(GObject *parent):
    GObject(parent)
{
    Display::Buffer * buf = new Display::Buffer(8,6);
    buf->setStaticData(triangle,9,5);
    m_objectBuffer = buf;
    setSizes(9,5);
}

DownTriangle::~DownTriangle()
{

}
