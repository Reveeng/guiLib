#ifndef GOBJECTBASE_H
#define GOBJECTBASE_H

#include <Event.h>
#include <GObjectRectangle.h>
#include <EventLoop.h>

using Coordinate = std::pair<uint32_t, uint32_t>;

class GObjectBase : public GObjectRectangle
{
public:
    GObjectBase();
    GObjectBase(uint32_t x, uint32_t y, uint32_t w, uint32_t h);

    void setX(uint32_t x);
    uint32_t x() const;

    void setY(uint32_t y);
    uint32_t y() const;

    void setPosition(uint32_t x, uint32_t y);

    void setWidth(uint32_t w);
    uint32_t width() const;

    void setHeight(uint32_t h);
    uint32_t height() const;

    void setSizes(uint32_t w, uint32_t h);

    void setVisible(bool v);
    bool visible()const;

protected:
    bool isCalledFromMainEventLoop() const;
    virtual void afterVisibleChanged() = 0;
    void setObjectEventLoop(EventLoop *loop);

    EventLoop *m_objectEventLoop;

private:
    bool m_visible;
};

#endif // GOBJECTBASE_H
