#ifndef DRAWBACKEND_H
#define DRAWBACKEND_H

#include <AbstractFrameBuffer.h>
#include <AbstractDisplayManager.h>

namespace Display{
class DrawBackend
{
public:
    DrawBackend();
    virtual ~DrawBackend();
//    void setDisplayBuffer(Abstraction::AbstractFrameBuffer *buf);
    void setDisplayManager(Abstraction::AbstractDisplayManager *manager);

//    void updateDisplayBuffer(const Abstraction::AbstractFrameBuffer * b, uint32_t x, uint32_t y);
//    void clearRectangle(uint32_t x, uint32_t y,uint32_t w, uint32_t h);

    void draw(Abstraction::AbstractFrameBuffer *buf);
    const Abstraction::AbstractDisplayManager &displayManager();


protected:
//    Abstraction::AbstractFrameBuffer *m_buffer;
    Abstraction::AbstractDisplayManager *m_manager;
};
}

#endif // DRAWBACKEND_H
