#include "Button.h"
#include <FontManager.h>


Button::Button(GObject *p):
    Rectangle(p),
    m_label(new Label(this))
{
    m_backgroundFill = false;
    m_borderWidth = 1;
    m_label->setAlignment(GObject::CenterIn);
}

Button::Button(const std::string &text, GObject *p):
    Rectangle(p),
    m_label(new Label(text, this))
{
    m_backgroundFill = false;
    m_borderWidth = 1;
    m_label->setAlignment(GObject::CenterIn);
}

void Button::setText(const std::string &text)
{
    m_label->setText(text);
}

std::string Button::text() const
{
    return m_label->text();
}

void Button::setFocused(bool f)
{
    setBorderWidth(f ? 3 : 1);
}

Label *Button::contentItem()
{
    return m_label;
}


