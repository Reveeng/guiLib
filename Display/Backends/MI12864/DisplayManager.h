#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include <AbstractDisplayManager.h>
#include <mutex>
//#include <

namespace Display{
    namespace MI12864{
    using Abstraction::AbstractDisplayBuffer;
    class DisplayManager : Abstraction::AbstractDisplayManager
    {
    public:
        DisplayManager(uint32_t c,
                       uint32_t mode,
                       bool enable);
        ~DisplayManager();

        virtual bool drawBuffer(const AbstractDisplayBuffer *buf) override final;

        virtual bool setContrast(uint32_t) override final;
        virtual uint32_t contrast()const override final;
        virtual bool setFlipMode(uint32_t) override final;
        virtual uint32_t flipMode() const override final;
        virtual bool setEnable(bool ) override final;
        virtual bool enable() const override final;

    private:

        mutable std::mutex m_oledLibMutex;
        bool m_isLibInited;
    };
    }
}

#endif // DISPLAYMANAGER_H
