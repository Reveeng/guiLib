#include "GObjectAnchors.h"
#include <utility>

bool operator==(const Anchor &a1, const Anchor &a2){
    return a1.objectRef() == a2.objectRef() &&
           a1.refType() == a2.refType() &&
           a1.offset() == a2.offset();
}

Anchor::Anchor(GObjectBase *ref):
    m_ref(ref),
    m_refType(None),
    m_offset(0)
{

}

Anchor::Anchor(const Anchor &o):
    m_ref(o.m_ref),
    m_refType(o.m_refType),
    m_offset(o.m_offset)
{

}

Anchor::Anchor(Anchor &&o):
    m_ref(std::move(o.m_ref)),
    m_refType(std::move(o.m_refType)),
    m_offset(std::move(o.m_offset))
{

}

//Anchor &Anchor::operator=(const Anchor &)
//{

//    if (
//    return *this;
//}

void Anchor::setObjectRef(GObjectBase *ref)
{
    m_ref = ref;
}

void Anchor::setRefType(AnchorType type)
{
    m_refType = type;
}

void Anchor::setOffset(uint32_t off)
{
    m_offset = off;
}

GObjectBase *Anchor::objectRef() const
{
    return m_ref;
}

AnchorType Anchor::refType() const
{
    return m_refType;
}

uint32_t Anchor::offset() const
{
    return m_offset;
}

bool Anchor::hasAnchor() const{
    return m_ref != nullptr;
}

uint32_t Anchor::refX(GObjectBase *p)
{
    if (p == m_ref){
        return m_refType == Left ? 0 : m_ref->width();
    }else{
        return m_refType == Left ? m_ref->x() : m_ref->x()+m_ref->width();
    }
}


uint32_t Anchor::refY(GObjectBase *p)
{
    if (p == m_ref){
        return m_refType == Top ? 0 : m_ref->height();
    }else{
        return m_refType == Top ? m_ref->y() : m_ref->y()+m_ref->height();
    }
}


/**/

GObjectAnchors::GObjectAnchors(GObjectBase *self):
    AbstractClass(self),
    m_self(self)
{
    createObjectSetter("left", m_anchors[Left]);
    createObjectSetter("right", m_anchors[Right]);
    createObjectSetter("top", m_anchors[Top]);
    createObjectSetter("bottom", m_anchors[Bottom]);

    createObjectGetter("left", m_anchors[Left]);
    createObjectGetter("right", m_anchors[Right]);
    createObjectGetter("top", m_anchors[Top]);
    createObjectGetter("bottom", m_anchors[Bottom]);

    connect("left",&GObjectAnchors::anchorChangeCallback, this);
    connect("right",&GObjectAnchors::anchorChangeCallback, this);
    connect("top",&GObjectAnchors::anchorChangeCallback, this);
    connect("bottom",&GObjectAnchors::anchorChangeCallback, this);
}

void GObjectAnchors::setParent(GObjectBase *parent)
{
    m_parent = parent;
}

bool GObjectAnchors::hasAnchor()
{
    bool has = false;
    for (auto &a : m_anchors){
        has |= a.hasAnchor();
    }
    return has;
}

void GObjectAnchors::setTopAnchor(AnchorType aType, GObjectBase *ref, uint32_t offset)
{
    Anchor an(ref);
    an.setRefType(aType);
    an.setOffset(offset);
    connect(ref, "aboutToDelete", this,&GObjectAnchors::anchoredObjectDeleted);
    invokeSetter("top", an);
}

void GObjectAnchors::setBottomAnchor(AnchorType aType, GObjectBase *ref, uint32_t offset)
{
    Anchor an(ref);
    an.setRefType(aType);
    an.setOffset(offset);
    connect(ref, "aboutToDelete", this,&GObjectAnchors::anchoredObjectDeleted);
    invokeSetter("bottom", an);
}

void GObjectAnchors::setRightAnchor(AnchorType aType, GObjectBase *ref, uint32_t offset)
{
    Anchor an(ref);
    an.setRefType(aType);
    an.setOffset(offset);
    connect(ref, "aboutToDelete", this,&GObjectAnchors::anchoredObjectDeleted);
    invokeSetter("right", an);
}

void GObjectAnchors::setLeftAnchor(AnchorType aType, GObjectBase *ref, uint32_t offset)
{
    Anchor an(ref);
    an.setRefType(aType);
    an.setOffset(offset);
    connect(ref, "aboutToDelete", this,&GObjectAnchors::anchoredObjectDeleted);
    invokeSetter("left", an);
}

void GObjectAnchors::anchorChangeCallback(Anchor)
{
    calculatePosition();
}

void GObjectAnchors::anchoredObjectDeleted(AbstractClass *o)
{
    auto f = [o](const Anchor &a){return a.objectRef() == o;};
    auto iter = std::find_if(m_anchors.begin(), m_anchors.end() , f);
    if (iter == m_anchors.end())
        return;
    iter->setObjectRef(nullptr);
    calculatePosition();
}

void GObjectAnchors::calculatePosition()
{
    uint32_t x = calculateX();
    uint32_t y = calculateY();
    uint32_t w = calculateWidth();
    uint32_t h = calculateHeight();
    m_self->setRectangle(x,y,w,h);
}


Anchor GObjectAnchors::get(AnchorType t){
    switch(t){
        case Top:
            return invokeGetter<Anchor>("top");
        case Bottom:
            return invokeGetter<Anchor>("bottom");
        case Right:
            return invokeGetter<Anchor>("right");
        case Left:
            return invokeGetter<Anchor>("left");
        default:
        return Anchor();
    }
}

uint32_t GObjectAnchors::calculateX()
{
    auto right = get(Right);
    auto left = get(Left);
    if (!right.hasAnchor() && !left.hasAnchor())
        return m_self->x();
    if (left.hasAnchor()){
        return left.refX(m_parent)+left.offset();
    }else{
        return right.refX(m_parent)-m_self->width()-right.offset();
    }
}

uint32_t GObjectAnchors::calculateY()
{
    auto top = get(Top);
    auto bot = get(Bottom);
    if (!top.hasAnchor() && !bot.hasAnchor())
        return m_self->y();

    if (top.hasAnchor()){
        return top.refY(m_parent)+top.offset();
    }else{
        return bot.refY(m_parent)-m_self->height()-bot.offset();
    }
}

uint32_t GObjectAnchors::calculateWidth()
{
    auto right = get(Right);
    auto left = get(Left);
    if (!right.hasAnchor() || !left.hasAnchor())
        return m_self->width();
    uint32_t lx = left.refX(m_parent)+left.offset();
    uint32_t rx = right.refX(m_parent)-right.offset();

    return rx-lx;
}

uint32_t GObjectAnchors::calculateHeight()
{
    auto top = get(Top);
    auto bot = get(Bottom);
    if (!top.hasAnchor() || !bot.hasAnchor())
        return m_self->height();
    uint32_t ty = top.refY(m_parent)+top.offset();
    uint32_t by = bot.refY(m_parent)-bot.offset();
    return by-ty;
}

