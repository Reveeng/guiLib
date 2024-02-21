#ifndef ABSTRACTFRAMEBUFFER_H
#define ABSTRACTFRAMEBUFFER_H

#include <cinttypes>
#include <DataContainer.h>

namespace Display
{
    namespace Abstraction
    {
        class AbstractFrameBuffer{
        public:
            virtual ~AbstractFrameBuffer(){

            }
            virtual DataContainer data() const = 0;
            virtual void mergeData(const AbstractFrameBuffer * buf, uint32_t x, uint32_t y) = 0;
            virtual void clearRectangle(uint32_t x,uint32_t y,uint32_t w,uint32_t h) = 0;

            virtual uint32_t width() const = 0 ;
            virtual uint32_t height() const = 0 ;

            virtual uint32_t bufferSize() const = 0;

            virtual void draw() = 0;
        };
    }
}

#endif // ABSTRACTFRAMEBUFFER_H
