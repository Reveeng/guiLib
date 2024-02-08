#ifndef GOBJECT_H
#define GOBJECT_H

#include <GObjectBase.h>
#include <AbstractFrameBuffer.h>
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

//    void setTopAnchor(GObject* o, AnchorType t);
//    void setBottomAnchor(GObject* o, AnchorType t);
//    void setRightAnchor(GObject* o, AnchorType t);
//    void setLeftAnchor(GObject* o, AnchorType t);

protected:
    virtual void updateBuffer() = 0;
    virtual void draw(bool force = false);
    void clear();
    virtual void afterObjectPositionChanged() override;
    virtual void afterObjectSizesChanged() override;
    virtual void afterVisibleChanged() override;

    void calculatePosition();

    void setBuffer(AbstractFrameBuffer *buf);

    Display::Abstraction::AbstractFrameBuffer *m_objectBuffer;

private:
    GObject * m_parent;
    std::vector<GObject*> m_children;
    Alignment m_alignment;

//    bool isVerticalBounded() const;
//    bool isHorizontalBounded() const;

    void calculatePositionAlignBased();
//    void calculateHorizontalPosition();

//    void calculateVerticalPosition();
//    void calculateNewY(const std::pair<GObject*,AnchorType> &p);
//    void calculateNewWidth(const std::pair<GObject*,AnchorType> &tp, const std::pair<GObject*,AnchorType> &bt);
//    std::array<std::pair<GObject*,AnchorType>,4> m_anchors;
};

#endif // GOBJECT_H
