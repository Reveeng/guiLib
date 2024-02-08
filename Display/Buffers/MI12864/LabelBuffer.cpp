#include "LabelBuffer.h"
#include <Fonts/MI12864/FontData.h>
#include <FontManager.h>

namespace Display{
    namespace MI12864{
        LabelBuffer::LabelBuffer(const std::string &data,
                                 const FontData *font):
            m_labelData(data)
        {
            if (font)
                m_font = font;
            else
                m_font = dynamic_cast<const FontData*>(FontManager::getDefaultFont());
        }

        LabelBuffer::~LabelBuffer()
        {

        }

        void LabelBuffer::setFont(const FontData *font)
        {
            m_font = font;
        }

        const std::string &LabelBuffer::labelData() const
        {
            return m_labelData;
        }

        void LabelBuffer::setLabelData(const std::string &data)
        {
            m_labelData = data;
        }

        DataContainer LabelBuffer::data() const
        {
            return m_font->getStringBitmap(m_labelData.c_str());
        }
        
        void LabelBuffer::mergeData(const AbstractFrameBuffer *, uint32_t, uint32_t)
        {

        }
        
        void LabelBuffer::clearRectangle(uint32_t, uint32_t , uint32_t , uint32_t )
        {
            
        }

        uint32_t LabelBuffer::width() const
        {
            return m_labelData.size()*m_font->symbolWidth();
        }

        uint32_t LabelBuffer::height() const
        {
            return m_font->symbolHeight();
        }

        uint32_t LabelBuffer::bufferSize() const
        {
            return m_font->symbolWidth()*m_font->symbolHeight()*m_labelData.size()/8;
        }
    }
}
