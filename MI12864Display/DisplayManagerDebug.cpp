#include "DisplayManagerDebug.h"
#include <iostream>
namespace Display{
DisplayManagerDebug::DisplayManagerDebug(uint32_t c,
                               uint32_t mode,
                               bool enable):
    Abstraction::AbstractDisplayManager(c,mode,enable)
{

}

DisplayManagerDebug::~DisplayManagerDebug()
{

}

bool DisplayManagerDebug::drawBuffer(const Abstraction::AbstractFrameBuffer *buf)
{
    uint32_t height = buf->height();
    uint32_t width = buf->width();
    const char *data = buf->data().data();
    for (uint32_t h = 1; h <= height; ++h){
        uint32_t H = h-1;
        uint32_t pageH = H/8;
        int pxE = (H - pageH*8);
        for (uint32_t w = 0; w < width; ++w){
            int offset = w+(pageH*width);
            char byte = *(data+offset);
            char bt = (byte &(1 << pxE));
            std::cout << (bt ? "1" : "0");
        }
        std::cout << '\n';
        if (h % 8 == 0 && h != 0)
            std::cout << '\n';
    }
    std::cout << "\n\n";
    return true;
}

bool DisplayManagerDebug::setContrast(uint32_t c)
{
    std::cout << "DisplayManagerDebug set contrast " << c << '\n';
    return true;
}

uint32_t DisplayManagerDebug::contrast() const
{
    std::cout << "DisplayManagerDebug get contast " << 256 << '\n';
    return 256;
}

bool DisplayManagerDebug::setFlipMode(uint32_t mode)
{
    std::cout << "DisplayManagerDebug set flip mode " << mode << '\n';
    return true;
}

uint32_t DisplayManagerDebug::flipMode() const
{
    std::cout << "DisplayManagerDebug get flip mode " << 0 << '\n';
    return 0;
}

bool DisplayManagerDebug::setEnable(bool e)
{
    std::cout << "DisplayManagerDebug set enable " << e << '\n';
    return true;
}

bool DisplayManagerDebug::enable() const
{
    std::cout << "DisplayManagerDebug get enable " << true << '\n';
    return true;
}

uint32_t DisplayManagerDebug::displayWidth() const
{
    return 128;
}

uint32_t DisplayManagerDebug::displayHeight() const
{
    return 64;
}
}
