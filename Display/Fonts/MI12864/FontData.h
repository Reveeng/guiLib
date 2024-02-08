#ifndef FONTDATA_H
#define FONTDATA_H

#include <AbstractFontContainer.h>
#include <string>
#include <cstring>

namespace Display{
    namespace MI12864{
    using Abstraction::DataContainer;
    class FontData : public Abstraction::AbstractFontContainer{

    public:
        FontData():
            Abstraction::AbstractFontContainer(0,0,0),
            m_asciiOffset(0),
            m_data(nullptr)
        {

        }
        FontData(const unsigned char *data,
                 uint8_t w,
                 uint8_t h,
                 uint32_t size,
                 uint8_t offset = 0):
            Abstraction::AbstractFontContainer(w,h,size),
            m_asciiOffset(offset),
            m_data(data)
        {

        }
        ~FontData()
        {

        }
        uint8_t asciiOffset() const
        {
            return m_asciiOffset;
        }

        virtual DataContainer getStringBitmap(const char *string) const override final
        {
            std::string label(string);
            char *data =  new char[label.size()*m_symbolWidth*m_symbolHeight/8];
            char *dataPtr = data;
            if (!data)
                return DataContainer(nullptr,false);
            int byteHeight = m_symbolHeight/9+1;
            for (char c : label){
                const unsigned char *bitmap = charBitmap(c);
                for (int h = 0; h < byteHeight; ++h){
                    char *tmpPtr = data+h*label.size()*m_symbolWidth;
                    std::memcpy(tmpPtr,bitmap, m_symbolWidth);
                }
                data += m_symbolWidth;
            }
            return DataContainer(dataPtr);
        }

    protected:
        const unsigned char *charBitmap(unsigned char c) const
        {
            if (c < m_asciiOffset || c > m_asciiOffset+m_tableSize)
                return m_data;
            if (c == 0xf8)
                return m_data+95*m_symbolWidth*(m_symbolHeight/9+1);

            int m_tableI = c-m_asciiOffset;
            return m_data+m_tableI*m_symbolWidth*(m_symbolHeight/9+1);
        }

    private:
        uint8_t m_asciiOffset;
        const unsigned char *m_data;

        friend class FontManager;
    };
    }
}

#endif // FONTDATA_H
