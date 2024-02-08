#ifndef ABSTRACTFONTCONTAINER_H
#define ABSTRACTFONTCONTAINER_H

#include <inttypes.h>
#include <DataContainer.h>

namespace Display{
namespace Abstraction {
    class AbstractFontContainer
    {
    public:
        /**
         * @brief AbstractFontContainer
         * @param w - symbol width in pixels
         * @param h - symbol height in pixels
         * @param size - number of symbols in font table
         */
        AbstractFontContainer(uint16_t w, uint16_t h, uint32_t size):
            m_symbolWidth(w),
            m_symbolHeight(h),
            m_tableSize(size)
        {

        }
        virtual ~AbstractFontContainer(){};

        uint16_t symbolWidth()const{return m_symbolWidth;}
        uint16_t symbolHeight()const{return m_symbolHeight;}
        uint32_t tableSize()const{return m_tableSize;}
        virtual DataContainer getStringBitmap(const char *string) const = 0;

    protected:

        uint16_t m_symbolWidth;
        uint16_t m_symbolHeight;
        uint32_t m_tableSize;
    };
}
}



#endif // ABSTRACTFONTCONTAINER_H
