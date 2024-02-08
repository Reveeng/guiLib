#ifndef DISPLAYBUFFER_H
#define DISPLAYBUFFER_H

#include <Buffers/MI12864/Buffer.h>
#include <AbstractDisplayBuffer.h>

namespace Display{
    namespace MI12864{
        class DisplayBuffer : public Abstraction::AbstractDisplayBuffer, public Buffer
        {
        public:
            DisplayBuffer(uint32_t w, uint32_t h);
            ~DisplayBuffer();

            virtual void appendBuffer(const AbstractFrameBuffer *b, uint32_t x = 0, uint32_t y = 0) override final;
            virtual void appendBuffer(const AbstractFrameBuffer &b, uint32_t x = 0, uint32_t y = 0) override final;
            virtual const char *getDisplayData() const override final;
            virtual uint32_t getDisplayDataSize() const override final;
            virtual void clearRectangle(uint32_t x, uint32_t y, uint32_t w, uint32_t h) override final;
            virtual uint32_t displayWidth() const override final;
            virtual uint32_t displayHeight() const override final;

        private:
            void appendPage(char *startIntData,const char *startExtData, uint32_t offset, uint32_t w);
            void clearPage(char *startIntData, char byte,uint32_t w);

        };
    }
}



#endif // DISPLAYBUFFER_H
