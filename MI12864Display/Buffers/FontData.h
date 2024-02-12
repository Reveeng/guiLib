#ifndef FONTDATA_H
#define FONTDATA_H

#include <AbstractFontContainer.h>
#include <string>
#include <cstring>

namespace Display{
using Abstraction::DataContainer;
class FontData : public Abstraction::AbstractFontContainer{

public:
    FontData();
    FontData(const unsigned char *data,
             uint8_t w,
             uint8_t h,
             uint32_t size,
             uint8_t offset = 0);
    ~FontData();
    uint8_t asciiOffset() const;

    virtual DataContainer getStringBitmap(const char *string, uint32_t mW) const override final;

protected:
    const unsigned char *charBitmap(unsigned char c) const;

private:
    uint8_t m_asciiOffset;
    const unsigned char *m_data;

    friend class FontManager;
};
}

#endif // FONTDATA_H
