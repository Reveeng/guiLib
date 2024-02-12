#include "Buffer.h"
#include <iostream>
#include <cstring>
namespace Display{

Buffer::Buffer():
    m_buffer(nullptr),
    m_stBuffer(nullptr),
    m_bufferSize(0),
    m_width(0),
    m_height(0)
{
}

Buffer::Buffer(const char *data, uint32_t w, uint32_t h):
    m_buffer(nullptr),
    m_stBuffer(nullptr),
    m_bufferSize(0),
    m_width(w),
    m_height(h)
{
    allocateMemory();
    copyData(data);
}

Buffer::Buffer(uint32_t w, uint32_t h):
    m_buffer(nullptr),
    m_stBuffer(nullptr),
    m_bufferSize(0),
    m_width(w),
    m_height(h)
{
    allocateMemory();
}

Buffer::Buffer(Buffer &o):
    m_buffer(o.m_buffer),
    m_stBuffer(o.m_stBuffer),
    m_bufferSize(o.m_bufferSize),
    m_width(o.m_width),
    m_height(o.m_height)
{

}

Buffer::Buffer(Buffer &&o):
    m_buffer(std::move(o.m_buffer)),
    m_stBuffer(std::move(o.m_stBuffer)),
    m_bufferSize(std::move(o.m_bufferSize)),
    m_width(std::move(o.m_width)),
    m_height(std::move(o.m_height))
{
    o.m_buffer = nullptr;
}


Buffer::~Buffer()
{
    clearMemory();
}

//void Buffer::init()
//{
//    clearMemory();
//    allocateMemory();
//}

void Buffer::setSizes(uint32_t w, uint32_t h)
{
    if (m_width == w && m_height == h)
        return;
    m_width = w;
    m_height = h;
    clearMemory();
    allocateMemory();
}

void Buffer::setWidth(uint32_t w)
{
    if (m_width == w || m_stBuffer)
        return;
    m_width = w;
    clearMemory();
    allocateMemory();
}

uint32_t Buffer::width() const
{
    return m_width;
}

void Buffer::setHeight(uint32_t h)
{
    if (m_height == h || m_stBuffer)
        return;
    m_height = h;
    clearMemory();
    allocateMemory();
}

uint32_t Buffer::height() const
{
    return m_height;
}

void Buffer::copyData(const char *data, uint32_t w, uint32_t h)
{
    w = w == 0 ? m_width : w;
    h = h == 0 ? m_height : h;
    setSizes(w,h);
    if (!m_buffer)
        return;
    std::memcpy(m_buffer, data,m_bufferSize);
}
void Buffer::setStaticData(const char *data, uint32_t w, uint32_t h){
    clearMemory();
    m_width = w;
    m_height = h;
    m_bufferSize = (m_height/8+1)*m_width;
    m_stBuffer = data;
}

char *Buffer::dataPtr()
{
    if (!m_buffer)
        allocateMemory();
    return m_buffer;
}

DataContainer Buffer::data() const
{
    return DataContainer(m_buffer,false);
}

void Buffer::appendPage(char *startIntData, const char *startExtData, uint32_t offset, uint32_t w)
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

void Buffer::mergeData(const AbstractFrameBuffer *b, uint32_t x, uint32_t y)
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
    uint32_t shift = y == 0 ? 0 : y-startPagePos*8;
    for (uint32_t hidx = 0; hidx <= b->height()/9; ++hidx){
        char* startByte = m_buffer+startPagePos*m_width+x;
        const char *bufSByte = data+hidx*b->width();
        uint32_t w = b->width()+x > m_width ? m_width-x : b->width();
        appendPage(startByte, bufSByte, shift,w);
        startPagePos += 1;
    }
}

void Buffer::clearRectangle(uint32_t x, uint32_t y, uint32_t w, uint32_t h)
{
    if (x > m_width || y > m_height)
        return;
    if (x+w > m_width)
        return;
    if (y+h > m_height)
        return;

    uint32_t startPage = y/8;
    uint32_t endPage = (y+h+1)/8;
    uint32_t diff = 1+endPage-startPage;
    for (uint32_t hidx = 0;hidx < diff; ++hidx){

        uint32_t topShift = 0;
        uint32_t bottomShift = 0;

        char *data = m_buffer+startPage*m_width+x;
        if (hidx == 0){
            topShift = y == 0 ? 0 : y-startPage*8;
        }
        if (hidx == diff-1){
            bottomShift = (endPage+1)*8-(y+h);
        }
        char fillByte = ~((0xFF << topShift)&(0xFF >> bottomShift));
        for (uint32_t widx = 0; widx < w; ++widx)
        {
            *(data+widx) &= fillByte;
        }
        startPage += 1;

    }
}

uint32_t Buffer::bufferSize() const
{
    return m_bufferSize;
}

void Buffer::draw()
{
    uint32_t height = m_height;
    uint32_t width = m_width;
    const char *data = m_buffer ? m_buffer : m_stBuffer;
    for (uint32_t h = 1; h <= height; ++h){
        uint32_t H = h-1;
        uint32_t pageH = (H)/8;
        int pxE = (H -pageH*8);
        for (uint32_t w = 0; w < width; ++w){
            int offset = w+(pageH*width);
            char byte = *(data+offset);
            char bt = (byte &(1 << pxE));
            std::cout << (bt ? "1" : "0");
        }
        std::cout << '\n';
        if (h % 8 == 0 && h != 0)
            std::cout << '\n';
    }
    std::cout << "\n\n";
}

//allocate (m_width+m_height)+1 bytes
bool Buffer::allocateMemory()
{
    uint32_t size = (m_height/8+1)*m_width;
    if (size == 0)
        return true;
    clearMemory();
    m_buffer = new char[size];
    if (!m_buffer)
        return false;
    m_bufferSize = size;
    clearBuffer();
    return true;
}

void Buffer::clearMemory(){
    delete[] m_buffer;
    m_buffer = nullptr;
    m_bufferSize = 0;
}

void Buffer::clearBuffer()
{
    std::memset(m_buffer,0,m_bufferSize);
}

}
