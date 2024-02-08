#ifndef ABSTRACTDISPLAYMANAGER_H
#define ABSTRACTDISPLAYMANAGER_H

#include <inttypes.h>
#include <AbstractFrameBuffer.h>

namespace Display
{
    namespace Abstraction
    {
        class AbstractDisplayManager
        {
        public:
            AbstractDisplayManager(uint32_t c,
                                   uint32_t mode,
                                   bool enable):
                m_contrast(c),
                m_flipMode(mode),
                m_enable(enable)
            {

            }
            virtual ~AbstractDisplayManager(){}

            virtual bool drawBuffer(const AbstractFrameBuffer *buff) = 0;

            virtual bool setContrast(uint32_t) = 0;
            virtual uint32_t contrast()const = 0;
            virtual bool setFlipMode(uint32_t) = 0;
            virtual uint32_t flipMode() const = 0;
            virtual bool setEnable(bool ) = 0;
            virtual bool enable() const = 0;

            virtual uint32_t displayWidth() const = 0;
            virtual uint32_t displayHeight() const = 0;

        protected:
            uint32_t m_contrast;
            uint32_t m_flipMode;
            bool m_enable;
        };
    }
}
#endif // ABSTRACTDISPLAYMANAGER_H
