#ifndef GOBJECTANCHORS_H
#define GOBJECTANCHORS_H

#include <GObjectRectangle.h>
#include <array>

enum AnchorType{
    Top = 0,
    Bottom,
    Left,
    Right,
    None
};

class Anchor{
public:
    Anchor(GObjectRectangle *ref = nullptr);
    Anchor(Anchor&o);
    Anchor(Anchor&&o);

    void setObjectRef(GObjectRectangle *ref);
    void setRerType(AnchorType type);
    void setOffset(uint32_t off);

    GObjectRectangle *objectRef() const;
    AnchorType refType() const;
    uint32_t offset() const;

    bool hasAnchor() const;

    uint32_t refX(GObjectRectangle *p);
    uint32_t refY(GObjectRectangle *p);

private:
    GObjectRectangle *m_ref;
    AnchorType m_refType;
    uint32_t m_offset;
};

class GObjectAnchors
{
public:


    GObjectAnchors(GObjectRectangle *self);
    void setParent(GObjectRectangle *parent);

    //ref should be parent of current item or they should have common parent
    template<AnchorType sType,AnchorType aType,
             typename std::enable_if_t<sType != None, bool> = true,
             typename std::enable_if_t<(((sType <= Bottom)&&(aType <= Bottom)) || ((sType >= Left) && (aType >= Left))),bool> = true>
    void setAnchor(GObjectRectangle *ref, uint32_t offset = 0)
    {
        m_anchors[sType].setObjectRef(ref);
        m_anchors[sType].setRerType(aType);
        m_anchors[sType].setOffset(offset);
    }

    void calculatePosition();

private:
    Anchor& get(AnchorType t);

    uint32_t calculateX();
    uint32_t calculateY();
    uint32_t calculateWidth();
    uint32_t calculateHeight();

    GObjectRectangle *m_self;
    GObjectRectangle *m_parent;

    std::array<Anchor,4> m_anchors;
    friend class GObject;
};

#endif // GOBJECTANCHORS_H
