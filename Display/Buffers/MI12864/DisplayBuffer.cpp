#include "DisplayBuffer.h"
namespace Display{
    namespace MI12864{
        DisplayBuffer::DisplayBuffer(uint32_t w, uint32_t h):
            AbstractDisplayBuffer(),
            Buffer(w,h)
        {
            dataPtr();
        }

        DisplayBuffer::~DisplayBuffer(){

        }

        void DisplayBuffer::appendPage(char *startIntData,const char *startExtData, uint32_t offset, uint32_t w)
        {
            for (uint32_t widx = 0; widx < w; ++widx){
                char shiftedByte = (startExtData[widx] << offset);
                *(startIntData+widx) |= shiftedByte;
                if (offset > 0 && offset < 8){
                    char byte = (0xff >> (8-offset))&(startExtData[widx] >> (8-offset));
                    *(startIntData+m_width+widx) |= byte;
                }
            }
        }

        void DisplayBuffer::clearPage(char *startIntData, char byte, uint32_t w)
        {
            for (uint32_t widx = 0; widx < w; ++widx){
                *(startIntData+widx) &= byte;
            }
        }

        void DisplayBuffer::appendBuffer(const AbstractFrameBuffer *b, uint32_t x, uint32_t y)
        {

            if (x > m_width || y > m_height)
                return;
            if (x+b->width() > m_width)
                return;
            if (y+b->height() > m_height)
                return;

            DataContainer cont = b->data();
            const char *data = cont.data();
            uint32_t startPagePos = y/8;
            for (uint32_t hidx = 0; hidx <= b->height()/8; ++hidx){
                char* startByte = m_buffer+startPagePos*m_width+x;
                const char *bufSByte = data+hidx*b->width();
                uint32_t shift = y == 0 ? 0 : hidx*y-startPagePos*8;
                uint32_t w = b->width()+x > m_width ? m_width-x : b->width();
                appendPage(startByte, bufSByte, shift,w);
                startPagePos += 1;
            }
        }

        void DisplayBuffer::appendBuffer(const AbstractFrameBuffer &b, uint32_t x, uint32_t y)
        {
            appendBuffer(&b,x,y);
        }

        const char* DisplayBuffer::getDisplayData() const
        {
            return m_buffer;
        }

        uint32_t DisplayBuffer::getDisplayDataSize() const
        {
            return m_bufferSize;
        }

        void DisplayBuffer::clearRectangle(uint32_t x, uint32_t y, uint32_t w, uint32_t h)
        {
            if (x > m_width || y > m_height)
                return;
            if (x+w > m_width)
                return;
            if (y+h > m_height)
                return;

            uint32_t startPage = y/8;
            for (uint32_t hidx = 0;hidx <= h/8; ++hidx){

                uint32_t topShift = 0;
                uint32_t bottomShift = 0;

                char *data = m_buffer+startPage*m_width+x;
                if (hidx == 0){
                    topShift = y = 0 ? 0: y-startPage*8;
                }
                if (hidx+1 == h/8+1){
                    bottomShift = (startPage+1)*8-(y+h);
                }
                char fillByte = (~(0xFF << topShift)&~(0xFF >> bottomShift));
                for (uint32_t widx = 0; widx < w; ++widx)
                {
                    *(data+widx) |= fillByte;
                }
                startPage += 1;

            }
        }

        uint32_t DisplayBuffer::displayWidth() const
        {
            return Buffer::width();
        }

        uint32_t DisplayBuffer::displayHeight() const
        {
            return Buffer::height();
        }
    }
}

