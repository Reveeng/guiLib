#ifndef GOBJECT_H
#define GOBJECT_H

#include <GObjectBase.h>
#include <AbstractFrameBuffer.h>
#include <GTimer.h>
#include <GObjectAnchors.h>
#include <vector>

using Coordinate = std::pair<uint32_t, uint32_t>;
using Display::Abstraction::AbstractFrameBuffer;
#include <iostream>

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

    template<AnchorType sT, AnchorType aT>
    void setAnchor(GObject *ref, uint32_t offset = 0){
        if (ref != m_parent && ref->parent() != m_parent){
            std::cout << "try to connect unconnectable objects\n";
            return;
        }
        Anchor & a = m_anchors.get(sT);
        GObject *obj = dynamic_cast<GObject*>(a.objectRef());
        if (obj)
            obj->removedAnchoredObject(this);
        m_anchors.setAnchor<sT,aT>(ref,offset);
        ref->m_anchoredObject.push_back(this);
        calculatePosition();
        redraw();
    }

protected:
    virtual void updateBuffer();
    virtual void redraw();
    void clear();
    virtual void afterObjectPositionChanged() override;
    virtual void afterObjectSizesChanged() override;
    virtual void afterVisibleChanged() override;

    virtual void calculatePosition();

    void removedAnchoredObject(GObject *o);

    void setBuffer(AbstractFrameBuffer *buf);

    Display::Abstraction::AbstractFrameBuffer *m_objectBuffer;

private:
    GObject * m_parent;
    std::vector<GObject*> m_children;
    std::vector<GObject *> m_anchoredObject;
    Alignment m_alignment;

    std::vector<GTimer*> m_timers;
    uint32_t m_timerIdGen;

    GObjectAnchors m_anchors;
    void calculatePositionAlignBased();
};

#endif // GOBJECT_H
