#include "Button.h"
#include <FontManager.h>
#include <MainWindow.h>


Button::Button(GObject *p):
    Rectangle(p),
    m_focused(false),
    m_label(new Label(this))
{
    m_backgroundFill = false;
    m_borderWidth = 0;
    declare_setter_getter(m_focused);
    bind_callback(m_focused,&Button::focusedChangedCallback);
    createObjectSetter("clicked");
}

Button::Button(const std::string &text, GObject *p):
    Rectangle(p),
    m_focused(false),
    m_label(new Label(text,MainWindow::displayWidth(), this))
{
    m_backgroundFill = false;
    m_borderWidth = 0;
    declare_setter_getter(m_focused);
    bind_callback(m_focused,&Button::focusedChangedCallback);
    createObjectSetter("clicked");
    calculateSize();
}

void Button::setText(const std::string &text)
{
    m_label->setText(text);
    calculateSize();
}

std::string Button::text() const
{
    return m_label->text();
}

void Button::setFocused(bool f)
{
    call_setter(m_focused,f);
}

bool Button::focused(){
    return call_getter(m_focused);
}

void Button::setTextAlignment(Alignment al)
{
    m_label->setAlignment(al);
}

void Button::emitClickedSignal()
{
    invokeSignal("clicked");
}

void Button::focusedChangedCallback(bool f)
{
    setBorderWidth(f ? 1 : 0);
    calculateSize();
}

Label *Button::contentItem()
{
    return m_label;
}

void Button::calculateSize(){
    uint32_t w = m_label->width();
    uint32_t h = m_label->height();
    m_label->setAlignment(GObject::CenterIn);
    setSizes(w+borderWidth()*2+2, h+m_borderWidth*2+2);
}


