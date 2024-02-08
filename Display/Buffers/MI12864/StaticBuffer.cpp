#include "StaticBuffer.h"

namespace Display{
    namespace MI12864{
        StaticBuffer::StaticBuffer(const char *data,
                                                     uint32_t w,
                                                     uint32_t h):
           m_width(w),
           m_height(h),
           m_data(data),
           m_bufferSize(m_width*m_height/8)
        {

        }

        DataContainer StaticBuffer::data() const
        {

            return m_data;
        }

        uint32_t StaticBuffer::width() const
        {
            return m_width;
        }

        uint32_t StaticBuffer::height() const
        {
            return m_height;
        }

        uint32_t StaticBuffer::bufferSize() const
        {
            return m_bufferSize;
        }
    }
}
