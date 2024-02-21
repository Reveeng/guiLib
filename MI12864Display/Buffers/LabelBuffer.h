#ifndef LABELBUFFER_H
#define LABELBUFFER_H

#include <AbstractFrameBuffer.h>
#include <string>
#include <FontData.h>

namespace Display{
using Abstraction::DataContainer;
class LabelBuffer : public Abstraction::AbstractFrameBuffer
{
public:
    LabelBuffer(const std::string &data, const FontData *font = nullptr);
    ~LabelBuffer();

    void setFont(const FontData *font);
    void setMaximumWidth(uint32_t w);

    const std::string &labelData() const;
    void setLabelData(const std::string &data);

    virtual DataContainer data() const override final;

    virtual void mergeData(const AbstractFrameBuffer *buf, uint32_t,uint32_t) override final;
    virtual void clearRectangle(uint32_t x,uint32_t y,uint32_t w,uint32_t h) override final;

    virtual uint32_t width() const override final;
    virtual uint32_t height() const override final;

    virtual uint32_t bufferSize() const override final;

    virtual void draw() override;

private:
    std::string m_labelData;
    const FontData *m_font;
    uint32_t m_maxWidth;
};
}


#endif // LABELBUFFER_H
