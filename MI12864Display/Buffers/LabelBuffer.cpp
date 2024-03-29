#include "LabelBuffer.h"
#include <FontData.h>
#include <iostream>

namespace Display{
LabelBuffer::LabelBuffer():
    m_font(nullptr),
    m_maxWidth(1024)
{

}

LabelBuffer::LabelBuffer(const std::string &data,
                         const FontData *font):
    m_labelData(data),
    m_font(nullptr),
    m_maxWidth(1024)
{
    if (font)
        m_font = font;
}

LabelBuffer::~LabelBuffer()
{

}

void LabelBuffer::setFont(const FontData *font)
{
    m_font = font;
}

void LabelBuffer::setMaximumWidth(uint32_t w)
{
    m_maxWidth = w;
}

const std::string &LabelBuffer::labelData() const
{
    return m_labelData;
}

void LabelBuffer::setLabelData(const std::string &data)
{
    m_labelData = data;
}

//void LabelBuffer::setInverse(bool inv)
//{
//    m_isInverse = inv;
//}

//bool LabelBuffer::isInverse() const
//{
//    return m_isInverse;
//}

DataContainer LabelBuffer::data() const
{
    if (!m_font)
        return DataContainer(nullptr,false);
    return m_font->getStringBitmap(m_labelData.c_str(), m_maxWidth);
}

void LabelBuffer::mergeData(const AbstractFrameBuffer *, uint32_t, uint32_t)
{

}

void LabelBuffer::clearRectangle(uint32_t, uint32_t , uint32_t , uint32_t )
{

}

uint32_t LabelBuffer::width() const
{
    uint32_t w = m_labelData.size()*m_font->symbolWidth();
    return w > m_maxWidth ? (m_maxWidth/m_font->symbolWidth())*m_font->symbolWidth() : w;
}

uint32_t LabelBuffer::height() const
{
    if (!m_font)
        return 0;
    return m_font->symbolHeight();
}

uint32_t LabelBuffer::bufferSize() const
{
    if (!m_font)
        return 0;
    return m_font->symbolWidth()*m_font->symbolHeight()*m_labelData.size()/8;
}

void LabelBuffer::draw()
{
    std::cout << "label buffer \n";
}
}
