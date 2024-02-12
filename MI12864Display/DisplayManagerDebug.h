#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include <AbstractDisplayManager.h>

namespace Display{
using Abstraction::AbstractFrameBuffer;
class DisplayManagerDebug : public Abstraction::AbstractDisplayManager
{
public:
    DisplayManagerDebug(uint32_t c,
                   uint32_t mode,
                   bool enable);
    ~DisplayManagerDebug();

    virtual bool drawBuffer(const AbstractFrameBuffer *buf) override final;

    virtual bool setContrast(uint32_t) override final;
    virtual uint32_t contrast()const override final;
    virtual bool setFlipMode(uint32_t) override final;
    virtual uint32_t flipMode() const override final;
    virtual bool setEnable(bool ) override final;
    virtual bool enable() const override final;

    virtual uint32_t displayWidth() const override final;
    virtual uint32_t displayHeight() const override final;
};
}


#endif // DISPLAYMANAGER_H
