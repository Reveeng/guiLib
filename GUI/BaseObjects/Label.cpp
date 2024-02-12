#include "Label.h"
#include <FontManager.h>
#include <LabelBuffer.h>

using namespace std::placeholders;
using Display::LabelBuffer;

Label::Label(GObject *parent):
    GObject(parent),
    m_fontName("")
{
    LabelBuffer *b = new LabelBuffer("", FontManager::getDefaultFont());
    b->setMaximumWidth(GObject::parent()->width());
    m_objectBuffer = b;

}

Label::Label(const std::string &text, const std::string &fontName,GObject* parent):
    GObject(parent),
    m_fontName(fontName)
{
    LabelBuffer *b = new LabelBuffer(text, FontManager::getFontData(fontName));
    b->setMaximumWidth(GObject::parent()->width());
    m_objectBuffer = b;
    setSizes(m_objectBuffer->width(), m_objectBuffer->height());
}

Label::~Label()
{

}

void Label::changeFont(const std::string &fontName)
{
    auto fd = FontManager::getFontData(fontName);
    if (!fd)
        return;
    if (!isCalledFromMainEventLoop()){
        auto slf = std::bind(&Label::changeFont,this, _1);
        Event<std::string> ev(slf, fontName);
        m_objectEventLoop->pushEvent(ev);
        return;
    }
    if (m_fontName == fontName)
        return;

    LabelBuffer *b = dynamic_cast<LabelBuffer*>(m_objectBuffer);
    b->setFont(fd);
    m_fontName = fontName;
    setSizes(b->width(), b->height());
    draw();
}

std::string Label::fontName() const
{
    if (!isCalledFromMainEventLoop()){
        auto slf = std::bind(&Label::fontName, this);
        WaitableEvent<std::string> ev(slf);
        m_objectEventLoop->pushEvent(ev);
        return ev.waitEventExecution();
    }
    return m_fontName;
}

void Label::setText(const std::string &t)
{
    if (!isCalledFromMainEventLoop()){
        auto slf = std::bind(&Label::setText,this, _1);
        Event<std::string> ev(slf, t);
        m_objectEventLoop->pushEvent(ev);
        return;
    }
    LabelBuffer *b = dynamic_cast<LabelBuffer*>(m_objectBuffer);
    if (t == b->labelData())
        return;
    b->setLabelData(t);
    setSizes(b->width(), b->height());
    draw();
}

std::string Label::text() const
{
    if (!isCalledFromMainEventLoop()){
        auto slf = std::bind(&Label::text, this);
        WaitableEvent<std::string> ev(slf);
        m_objectEventLoop->pushEvent(ev);
        return ev.waitEventExecution();
    }
    LabelBuffer *b = dynamic_cast<LabelBuffer*>(m_objectBuffer);
    return b->labelData();
}

void Label::updateBuffer()
{
}

void Label::calculatePosition()
{
    LabelBuffer *b = dynamic_cast<LabelBuffer*>(m_objectBuffer);
    b->setMaximumWidth(parent()->width());
    GObject::calculatePosition();
    draw();
}
