#ifndef ABSTRACTDRAWBACKEND_H
#define ABSTRACTDRAWBACKEND_H

#include <AbstractFrameBuffer.h>
#include <AbstractDisplayBuffer.h>
#include <AbstractDisplayManager.h>

namespace Display
{
    namespace Abstraction
    {
        class AbstractDrawBackend
        {
        public:
            AbstractDrawBackend(){}
            virtual ~AbstractDrawBackend(){}
            void setDisplayBuffer(AbstractDisplayBuffer *buf)
            {
                m_buffer = buf;
            }

            void setDisplayManager(AbstractDisplayManager *manager)
            {
                m_manager = manager;
            }

            void updateDisplayBuffer(const AbstractFrameBuffer * b, uint32_t x, uint32_t y)
            {
                m_buffer->appendBuffer(b, x,y);
            }
            void updateDisplayBuffer(const AbstractFrameBuffer &b, uint32_t x, uint32_t y)
            {
                m_buffer->appendBuffer(b, x,y);
            }

            void clearRectangle(uint32_t x, uint32_t y,uint32_t w, uint32_t h)
            {
                m_buffer->clearRectangle(x,y,w,h);
            }

            void draw()
            {
                m_manager->drawBuffer(m_buffer);
            };

            const AbstractDisplayManager &displayManager()
            {
                return *m_manager;
            }


        protected:
            AbstractDisplayBuffer *m_buffer;
            AbstractDisplayManager *m_manager;
        };
    }
}
#endif // ABSTRACTDRAWBACKEND_H
