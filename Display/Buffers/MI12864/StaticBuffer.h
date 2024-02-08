#ifndef STATICBUFFER_H
#define STATICBUFFER_H

#include <AbstractFrameBuffer.h>

namespace Display {
    namespace MI12864{
        using Abstraction::DataContainer;
        class StaticBuffer : public Abstraction::AbstractFrameBuffer
        {
        public:
            StaticBuffer(const char * data, uint32_t w, uint32_t h);

            virtual DataContainer data() const override final;
            virtual uint32_t width() const override final;
            virtual uint32_t height() const override final;
            virtual uint32_t bufferSize() const override final;

        private:
            uint32_t m_width;
            uint32_t m_height;
            const char *m_data;
            uint32_t m_bufferSize;
        };
    }
}

#endif // STATICBUFFER_H
