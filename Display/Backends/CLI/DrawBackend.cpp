#include "DrawBackend.h"
#include <Backends/CLI/DisplayManager.h>
#include <iostream>

namespace Display{
    namespace CLI{
    DrawBackend::DrawBackend():
        AbstractDrawBackend()
    {
        setDisplayManager()
    }

    DrawBackend::~DrawBackend()
    {

    }

//    void DrawBackend::drawScene()
//    {
//        uint32_t height = m_buffer->displayHeight();
//        uint32_t width = m_buffer->displayWidth();
//        const char *data = m_buffer->getDisplayData();
//        for (uint32_t h = 0; h < height; ++h){
//            uint32_t pageH = h/8;
//            int pxE = (h - pageH*8+1);
//            for (uint32_t w = 0; w < width; ++w){
//                char byte = *(data+w+(pageH*width));
//                std::cout << ((byte &(1 << pxE)) ? "1" : "0");
//            }
//            std::cout << '\n';
//        }
//    }
    }
}

