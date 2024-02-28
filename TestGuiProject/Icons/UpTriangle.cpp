#include "UpTriangle.h"
#include <Buffer.h>

static char triangle[] = {0x10,0x18,0x1c,0x1e,0x1f,0x1e, 0x1c,0x18,0x10};

UpTriangle::UpTriangle(GObject *parent) :
    GObject(parent)
{
    Display::Buffer *buf = new Display::Buffer(8,6);
    buf->setStaticData(triangle, 9, 5);
    m_objectBuffer = buf;
    setSizes(9,5);
}

UpTriangle::~UpTriangle()
{

}
