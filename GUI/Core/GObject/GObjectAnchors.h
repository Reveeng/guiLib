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
    Anchor(GObjectBase *ref = nullptr);
    Anchor(Anchor&o);
    Anchor(Anchor&&o);

    void setObjectRef(GObjectBase *ref);
    void setRerType(AnchorType type);
    void setOffset(uint32_t off);

    GObjectBase *objectRef() const;
    AnchorType refType() const;
    uint32_t offset() const;

    bool hasAnchor() const;

    uint32_t refX(GObjectBase *p);
    uint32_t refY(GObjectBase *p);

private:
    GObjectBase *m_ref;
    AnchorType m_refType;
    uint32_t m_offset;
};

class GObjectAnchors
{
public:


    GObjectAnchors(GObjectBase *self);
    void setParent(GObjectBase *parent);

    //ref should be parent of current item or they should have common parent
    template<AnchorType sType,AnchorType aType,
             typename std::enable_if_t<sType != None, bool> = true,
             typename std::enable_if_t<(((sType <= Bottom)&&(aType <= Bottom)) || ((sType >= Left) && (aType >= Left))),bool> = true>
    void setAnchor(GObjectBase *ref, uint32_t offset = 0)
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

    GObjectBase *m_self;
    GObjectBase *m_parent;

    std::array<Anchor,4> m_anchors;
    friend class GObject;
};

#endif // GOBJECTANCHORS_H
