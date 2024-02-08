#include "DisplayManager.h"
#include <mutex>

//#include <oled.h>
namespace Display{
    namespace MI12864{

    using MutexGuard = std::lock_guard<std::mutex>;
DisplayManager::DisplayManager(uint32_t c,
                               uint32_t mode,
                               bool enable):
    Abstraction::AbstractDisplayManager(c,mode,enable),
    m_isLibInited(false)
{
//    m_isLibInited = oled_init(OLED_I2C_BUS, OLED_I2C_ADDR_0) == 0;
//    m_isLibInited |= oled_reset() == 0;
    setContrast(m_contrast);
    setFlipMode(m_flipMode);
    setEnable(m_enable);
}

DisplayManager::~DisplayManager()
{
    MutexGuard g(m_oledLibMutex);
//    if (m_isLibInited)
//        oled_exit();
}

bool DisplayManager::drawBuffer(const Abstraction::AbstractDisplayBuffer *buf)
{
    MutexGuard g(m_oledLibMutex);
//    return oled_draw_buffer(buf->getDisplayData(), buf->getDisplayDataSize()) == 0;
    return true;
}

bool DisplayManager::setContrast(uint32_t c)
{
    MutexGuard g(m_oledLibMutex);
    if (c == m_contrast)
        return true;
//    int ret = oled_contrast(c);
//    if (ret == 0)
//        m_contrast = c;
//    return ret == 0;
    return true;
}

uint32_t DisplayManager::contrast() const
{
    MutexGuard g(m_oledLibMutex);
    return m_contrast;
}

bool DisplayManager::setFlipMode(uint32_t mode)
{
    MutexGuard g(m_oledLibMutex);
    if (m_flipMode == mode)
        return true;
//    int ret = oled_flip(mode);
//    if (ret == 0)
//        m_flipMode = mode;
//    return ret == 0;
    return true;
}

uint32_t DisplayManager::flipMode() const
{
    MutexGuard g(m_oledLibMutex);
    return m_flipMode;
}

bool DisplayManager::setEnable(bool e)
{
    MutexGuard g(m_oledLibMutex);
    if (m_enable == e)
        return true;
//    int ret = oled_on(e);
//    if (ret == 0)
//        m_enable = e;
//    return ret == 0;
    return true;
}

bool DisplayManager::enable() const
{
    MutexGuard g(m_oledLibMutex);
    return m_enable;
}

    }
}
