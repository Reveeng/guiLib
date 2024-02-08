#ifndef ABSTRACTDISPLAYBUFFER_H
#define ABSTRACTDISPLAYBUFFER_H
#include <AbstractFrameBuffer.h>


namespace Display
{
    namespace Abstraction
    {
        class AbstractDisplayBuffer
        {
        public:
            virtual ~AbstractDisplayBuffer(){

            }
//            virtual void appendBuffer(const AbstractFrameBuffer *n, uint32_t x = 0, uint32_t y = 0) = 0;
//            virtual void appendBuffer(const AbstractFrameBuffer &b,uint32_t x = 0, uint32_t y = 0) = 0;
//            virtual const char * getDisplayData() const = 0;
//            virtual uint32_t getDisplayDataSize() const = 0;
//            virtual void clearRectangle(uint32_t x, uint32_t y, uint32_t w, uint32_t h) = 0;
//            virtual uint32_t displayWidth() const = 0;
//            virtual uint32_t displayHeight() const = 0;
        };
    }
}


#endif // ABSTRACTDISPLAYBUFFER_H
