#ifndef GOBJECT_H
#define GOBJECT_H

#include <GObjectRectangle.h>
#include <AbstractFrameBuffer.h>
#include <GObjectAnchors.h>
#include <GTimer.h>
#include <vector>

using Coordinate = std::pair<uint32_t, uint32_t>;
using Display::Abstraction::AbstractFrameBuffer;
#include <iostream>

#define declare_setter_getter(x) createObjectSetter(#x,x);createObjectGetter(#x,x)
#define call_setter(x, f) invokeSetter(#x,f)
#define call_getter(x) invokeGetter<typeof(x)>(#x)
#define bind_callback(x, f) connect(#x, f, this)
class GObject;

class GObjectContainer : public std::vector<GObject*>
{
public:
    void calculatePositions();
    void print_data();
};

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
    Alignment alignment();

    void setInversion(bool inv);
    bool inversion() const;

    const Display::Abstraction::AbstractFrameBuffer *buffer();

    uint32_t startTimer(std::function<void()> f,uint32_t time, bool isSingleShot = false);
    void stopTimer(uint32_t id);

    void setAnchor(AnchorType t1, GObject *ref, AnchorType t2, uint32_t offset);

protected:
    virtual void updateBuffer();
    virtual void redraw();
    void clear();

    virtual void calculatePosition();
    void removeChild(GObject *obj);

    void setBuffer(AbstractFrameBuffer *buf);

    Display::Abstraction::AbstractFrameBuffer *m_objectBuffer;


protected://callbacks
    virtual void positionChangedCallback(Rect newR) override;
    void alignmentChanged(int);
    void visibleChangedCallback(bool visible);

    void onDeleteCallback(AbstractClass *o);
    void inverseChanged(bool isinv);

protected:
    bool isPositionChanged(Rect &rect);
    bool isSizesChanged(Rect &rect);



private:
    GObject * m_parent;
    GObjectContainer m_children;

    GObjectContainer m_anchoredObjects;

    int m_alignment;
    bool m_inverse;

    std::vector<GTimer*> m_timers;
    uint32_t m_timerIdGen;

    GObjectAnchors m_anchors;
    Rect m_prevPos;
    void calculatePositionAlignBased();

    friend class GObjectContainer;
};

#endif // GOBJECT_H
