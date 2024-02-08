#include "DrawBackend.h"
#include <AbstractFrameBuffer.h>
#include <AbstractDisplayBuffer.h>
#include <AbstractDisplayManager.h>

namespace Display{
    using namespace Abstraction;

    DrawBackend::DrawBackend(){}
    DrawBackend::~DrawBackend(){}

    void DrawBackend::setDisplayBuffer(AbstractFrameBuffer *buf)
    {
        m_buffer = buf;
    }
    void DrawBackend::setDisplayManager(AbstractDisplayManager *manager)
    {
        m_manager = manager;
    }


    void DrawBackend::updateDisplayBuffer(const Abstraction::AbstractFrameBuffer * b, uint32_t x, uint32_t y)
    {
        m_buffer->mergeData(b, x,y);
    }
//    void DrawBackend::updateDisplayBuffer(const Abstraction::AbstractFrameBuffer &b, uint32_t x, uint32_t y)
//    {
//        m_buffer->mergeData(b, x,y);
//    }

    void DrawBackend::clearRectangle(uint32_t x, uint32_t y,uint32_t w, uint32_t h)
    {
        m_buffer->clearRectangle(x,y,w,h);
    }

    void DrawBackend::draw()
    {
        m_manager->drawBuffer(m_buffer);
    };

    const AbstractDisplayManager &DrawBackend::displayManager()
    {
        return *m_manager;
    }
}

