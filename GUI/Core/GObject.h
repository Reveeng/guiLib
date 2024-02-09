#ifndef GOBJECT_H
#define GOBJECT_H

#include <GObjectBase.h>
#include <AbstractFrameBuffer.h>
#include <GTimer.h>
#include <vector>

using Coordinate = std::pair<uint32_t, uint32_t>;
using Display::Abstraction::AbstractFrameBuffer;

class GObject : public GObjectBase
{
public:
    //alignment to parent
    enum Alignment{
        NoAlign,
        VCenter,
        HCenter,
        CenterIn
    };

    enum AnchorType{
        Top,
        Bottom,
        Right,
        Left
    };

    GObject(GObject *parent);
    GObject(uint32_t x, uint32_t y, uint32_t w, uint32_t h,GObject *parent);
    virtual ~GObject();

    GObject *parent() const;
    void setParent(GObject *p);
    const std::vector<GObject*> &children() const;

    void setAlignment(Alignment al);

    GTimer *getTimer();
    uint32_t startTimer(std::function<void()> f,uint32_t time, bool isSingleShot = false);
    void stopTimer(uint32_t id);

protected:
    virtual void updateBuffer() = 0;
    virtual void draw(bool force = false);
    void clear();
    virtual void afterObjectPositionChanged() override;
    virtual void afterObjectSizesChanged() override;
    virtual void afterVisibleChanged() override;

    virtual void calculatePosition();

    void setBuffer(AbstractFrameBuffer *buf);

    Display::Abstraction::AbstractFrameBuffer *m_objectBuffer;

private:
    GObject * m_parent;
    std::vector<GObject*> m_children;
    Alignment m_alignment;

    std::vector<GTimer*> m_timers;
    uint32_t m_timerIdGen;

    void calculatePositionAlignBased();
};

#endif // GOBJECT_H
