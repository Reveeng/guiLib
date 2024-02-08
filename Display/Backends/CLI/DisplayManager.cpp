#include "DisplayManager.h"
#include <iostream>
namespace Display{
    namespace CLI{
DisplayManager::DisplayManager(uint32_t c,
                               uint32_t mode,
                               bool enable):
    Abstraction::AbstractDisplayManager(c,mode,enable)
{

}

DisplayManager::~DisplayManager()
{

}

bool DisplayManager::drawBuffer(const Abstraction::AbstractFrameBuffer *buf)
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

bool DisplayManager::setContrast(uint32_t c)
{
    std::cout << "DisplayManager set contrast " << c << '\n';
    return true;
}

uint32_t DisplayManager::contrast() const
{
    std::cout << "DisplayManager get contast " << 256 << '\n';
    return 256;
}

bool DisplayManager::setFlipMode(uint32_t mode)
{
    std::cout << "DisplayManager set flip mode " << mode << '\n';
    return true;
}

uint32_t DisplayManager::flipMode() const
{
    std::cout << "DisplayManager get flip mode " << 0 << '\n';
    return 0;
}

bool DisplayManager::setEnable(bool e)
{
    std::cout << "DisplayManager set enable " << e << '\n';
    return true;
}

bool DisplayManager::enable() const
{
    std::cout << "DisplayManager get enable " << true << '\n';
    return true;
}

uint32_t DisplayManager::displayWidth() const
{
    return 128;
}

uint32_t DisplayManager::displayHeight() const
{
    return 64;
}

    }
}
