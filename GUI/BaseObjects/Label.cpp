#include "Label.h"
#include <FontManager.h>
#include <LabelBuffer.h>

using namespace std::placeholders;
using Display::LabelBuffer;

Label::Label(GObject *parent):
    GObject(parent),
    m_fixedSize(false),
    m_fontName("")
{
    initFunctions();
    LabelBuffer *b = new LabelBuffer("", FontManager::getDefaultFont());
    b->setMaximumWidth(GObject::parent()->width());
    m_objectBuffer = b;

}
Label::Label(const std::string &text, GObject *p):
    GObject(p),
    m_fixedSize(false),
    m_fontName(""),
    m_text(text)
{
    initFunctions();
    LabelBuffer *b = new LabelBuffer(text, FontManager::getDefaultFont());
    b->setMaximumWidth(GObject::parent()->width());
    m_objectBuffer = b;
    setSizes(m_objectBuffer->width(), m_objectBuffer->height());
}

Label::Label(const std::string &text, const std::string &fontName,GObject* parent):
    GObject(parent),
    m_fixedSize(false),
    m_fontName(fontName),
    m_text(text)
{
    initFunctions();
    LabelBuffer *b = new LabelBuffer(text, FontManager::getFontData(fontName));
    b->setMaximumWidth(GObject::parent()->width());
    m_objectBuffer = b;
    setSizes(m_objectBuffer->width(), m_objectBuffer->height());
}

Label::Label(const std::string &txt,uint32_t mWidth, GObject *p):
    GObject(p),
    m_fixedSize(true),
    m_fontName(""),
    m_text(txt)
{
    initFunctions();
    LabelBuffer *b = new LabelBuffer(txt, FontManager::getDefaultFont());
    b->setMaximumWidth(mWidth);
    m_objectBuffer = b;
    uint32_t w = m_objectBuffer->width();
    uint32_t h = m_objectBuffer->height();
    setSizes(w, h);
}

Label::~Label()
{

}

void Label::changeFont(const std::string &fontName)
{
    call_setter(m_fontName,fontName);
}

std::string Label::fontName()
{
    return call_getter(m_fontName);
}

void Label::setText(const std::string &t)
{
    call_setter(m_text,t);
}

std::string Label::text()
{
    return call_getter(m_text);
}

void Label::updateBuffer()
{
    if (!parent())
        return;

    LabelBuffer *b = dynamic_cast<LabelBuffer*>(m_objectBuffer);
    b->setLabelData(m_text);
    auto fd = FontManager::getFontData(m_fontName);
    if (!fd)
        return;
    b->setFont(fd);
    if (!m_fixedSize)
        b->setMaximumWidth(parent()->width());
    setSizes(m_objectBuffer->width(), m_objectBuffer->height());
    GObject::updateBuffer();
}

void Label::calculatePosition()
{
    LabelBuffer *b = dynamic_cast<LabelBuffer*>(m_objectBuffer);
    if (!m_fixedSize)
        b->setMaximumWidth(parent()->width());
    GObject::calculatePosition();
    redraw();
}

void Label::textChanged(std::string)
{
    updateBuffer();
    redraw();
}

void Label::fontChanged(std::string)
{
    updateBuffer();
    redraw();
}

void Label::initFunctions()
{
    declare_setter_getter(m_fontName);
    declare_setter_getter(m_text);
    bind_callback(m_fontName,&Label::fontChanged);
    bind_callback(m_text,&Label::textChanged);
}
