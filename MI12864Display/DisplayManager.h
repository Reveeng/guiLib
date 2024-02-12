#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include <AbstractDisplayManager.h>
#include <AbstractFrameBuffer.h>
#include <mutex>

namespace Display{
using Abstraction::AbstractFrameBuffer;
class DisplayManager : Abstraction::AbstractDisplayManager
{
public:
    DisplayManager(uint32_t c,
                   uint32_t mode,
                   bool enable);
    ~DisplayManager();

    virtual bool drawBuffer(const AbstractFrameBuffer *buf) override final;

    virtual bool setContrast(uint32_t) override final;
    virtual uint32_t contrast()const override final;
    virtual bool setFlipMode(uint32_t) override final;
    virtual uint32_t flipMode() const override final;
    virtual bool setEnable(bool ) override final;
    virtual bool enable() const override final;

    virtual uint32_t displayWidth() const override final;
    virtual uint32_t displayHeight() const override final;

private:

    mutable std::mutex m_oledLibMutex;
    bool m_isLibInited;
};
}

#endif // DISPLAYMANAGER_H
