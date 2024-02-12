#include <FontData.h>


Display::FontData::FontData():
    Abstraction::AbstractFontContainer(0,0,0),
    m_asciiOffset(0),
    m_data(nullptr)
{

}

Display::FontData::FontData(const unsigned char *data, uint8_t w, uint8_t h, uint32_t size, uint8_t offset):
    Abstraction::AbstractFontContainer(w,h,size),
    m_asciiOffset(offset),
    m_data(data)
{

}

Display::FontData::~FontData()
{

}

uint8_t Display::FontData::asciiOffset() const
{
    return m_asciiOffset;
}

Display::DataContainer Display::FontData::getStringBitmap(const char *string, uint32_t mW) const
{
    std::string label(string);
    uint32_t maxSymbolsSize = mW/m_symbolWidth;
    uint32_t predW = label.size() > maxSymbolsSize ? maxSymbolsSize : label.size();

    uint32_t bufSize = predW*m_symbolWidth*(m_symbolHeight/9+1);
    char *data =  new char[bufSize];
    std::memset(data,0,bufSize);
    char *dataPtr = data;
    if (!data)
        return DataContainer(nullptr,false);
    int byteHeight = m_symbolHeight/9+1;
    for (uint32_t i = 0; i < predW; ++i){
        const unsigned char *bitmap = charBitmap(label[i]);
        for (int h = 0; h < byteHeight; ++h){
            int offset = h*predW*m_symbolWidth;
            char *tmpPtr = data+offset;
            std::memcpy(tmpPtr,bitmap, m_symbolWidth);
        }
        data += m_symbolWidth;
    }
    return DataContainer(dataPtr);
}

const unsigned char *Display::FontData::charBitmap(unsigned char c) const
{
    if (c < m_asciiOffset || c > m_asciiOffset+m_tableSize)
        return m_data;
    if (c == 0xf8)
        return m_data+95*m_symbolWidth*(m_symbolHeight/9+1);

    int m_tableI = c-m_asciiOffset;
    return m_data+m_tableI*m_symbolWidth*(m_symbolHeight/9+1);
}
