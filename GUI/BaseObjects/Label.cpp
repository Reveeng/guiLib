#include "Label.h"
#include <FontManager.h>
#include <Buffers/MI12864/Buffer.h>

using namespace std::placeholders;
using Display::MI12864::LabelBuffer;

Label::Label(GObject *parent):
    GObject(parent),
    m_fontName("")
{
    m_objectBuffer = new LabelBuffer("");
}

Label::Label(const std::string &text, const std::string &fontName,GObject* parent):
    GObject(parent),
    m_fontName(fontName)
{
    m_objectBuffer = new LabelBuffer(text, Display::FontManager::getFontData(fontName));
    setSizes(m_objectBuffer->width(), m_objectBuffer->height());
}

Label::~Label()
{

}

void Label::changeFont(const std::string &fontName)
{
    auto fd = Display::FontManager::getFontData(fontName);
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
    updateBuffer();
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
    updateBuffer();
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
