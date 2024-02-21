#ifndef BUFFER_H
#define BUFFER_H


#include <cinttypes>
#include <AbstractFrameBuffer.h>

namespace Display{
using Abstraction::DataContainer;
class Buffer : public Abstraction::AbstractFrameBuffer
{
public:
    /**
     * @brief create empty container and set with and height
     * @param dWidth - dispaly width in pixels
     * @param dHeight - display height in pixels
     */
    Buffer(uint32_t w, uint32_t h);
    /**
     * @brief allocate plain memory and copy given data
     * @param buf - pointer to data to copy
     * @param w - width of memory in pixels (in bits)
     * @param h -  height of memory in pixel (in bits)
     */
    Buffer(const char * buf, uint32_t w , uint32_t h);
    /**
     * @brief create empty buffer container
     */
    Buffer();
    Buffer(Buffer &o);
    Buffer(Buffer &&o);

    ~Buffer();

    /**
     * @brief set new width and height for buffer, allocate buffer for data
     * @param w - new width
     * @param h - new height
     */
    void setSizes(uint32_t w, uint32_t h);
    /**
     * @brief set new width for buffer. Reallocate dynamic memory
     * @param w - new buffer width
     */
    void setWidth(uint32_t w);
    /**
     * @brief set new Height for buffer. Reallocate dynamic memory
     * @param h
     */
    void setHeight(uint32_t h);

    /**
     * @brief get current width of buffer
     * @return uint32_t width
     */
    virtual uint32_t width() const override final;
    /**
     * @brief get current height of buffer
     * @return uint32_t height
     */
    virtual uint32_t height() const override final;

    /**
     * @brief copy data from
     * @param src - ptr to data that need to be copied
     * @param w - width of given data. if w=0 then will be used width that stored inside container
     * @param h - height of given data. if h=0 then will be used height stored indisde container
     */
    void copyData(const char * src, uint32_t w = 0, uint32_t h = 0);
    /**
     * @brief store ptr to data that allocated somewhere and will not be modified or deleted
     * @param data - pointer to data
     * @param w - data width
     * @param h - data height
     */
    void setStaticData(const char *data, uint32_t w, uint32_t h);

    /**
     * @brief get pointer to modifiable data
     * @return pointer to data or nullptr if no data available data or buffer contain static data
     */
    char *dataPtr();

    /**
     * @brief get DataContainer that wraps data inside buffer
     * @return
     */
    virtual DataContainer data() const override final;
    /**
     * @brief merge data from another buffer to current buffer. Data will be add started from x and y coordinates. If buffer larger than current buffer data will be croped
     * @param buf - buffer that need to be merged
     * @param x - start x coordinate
     * @param y - start y coordinate
     */
    virtual void mergeData(const AbstractFrameBuffer * buf, uint32_t x, uint32_t y) override final;
    /**
     * @brief clear data in rectangle buffer
     * @param x - reactngles left up angle x coordinate
     * @param y - reactngles left up angle y coordinate
     * @param w - width of rectangle
     * @param h - height of rectangle
     */
    virtual void clearRectangle(uint32_t x,uint32_t y,uint32_t w,uint32_t h) override final;

    /**
     * @brief get buffer size in bytes
     * @return
     */
    virtual uint32_t bufferSize() const override final;

    //debug func
    virtual void draw() override;

    /**
     * @brief set all bytes to zero. Function dont free allocated memory
     */
    void clearBuffer();


protected:
    char *m_buffer;
    const char *m_stBuffer;
    uint32_t m_bufferSize;

    uint32_t m_width;
    uint32_t m_height;

private:
    void appendPage(char *startIntData,const char *startExtData, uint32_t offset, uint32_t w);

    bool allocateMemory();
    void clearMemory();
};
}
#endif // BUFFER_H
