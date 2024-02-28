#include "CheckIcon.h"
#include <Buffer.h>

static char data[] = {0x18,0x30,0x60,0x30,0x18,0xc,0x6,0x3};

CheckIcon::CheckIcon(GObject *parent):
    GObject(parent)
{
    Display::Buffer * buf = new Display::Buffer(8,7);
    buf->setStaticData(data,8,7);
    m_objectBuffer = buf;
}

CheckIcon::~CheckIcon()
{

}
