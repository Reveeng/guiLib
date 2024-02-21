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
    Anchor(const Anchor&o);
    Anchor(Anchor&&o);
    Anchor &operator=(const Anchor&) = default;

    void setObjectRef(GObjectBase *ref);
    void setRefType(AnchorType type);
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

class GObjectAnchors : public AbstractClass
{
public:


    GObjectAnchors(GObjectBase *self);
    void setParent(GObjectBase *parent);
    bool hasAnchor();

    //ref should be parent of current item or they should have common parent
    void setTopAnchor(AnchorType aType, GObjectBase *ref, uint32_t offset);
    void setBottomAnchor(AnchorType aType, GObjectBase *ref, uint32_t offset);
    void setRightAnchor(AnchorType aType, GObjectBase *ref, uint32_t offset);
    void setLeftAnchor(AnchorType aType, GObjectBase *ref, uint32_t offset);

    void calculatePosition();

protected:
    void anchorChangeCallback(Anchor );
    void anchoredObjectDeleted(AbstractClass *o);

private:
    Anchor get(AnchorType t);

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
