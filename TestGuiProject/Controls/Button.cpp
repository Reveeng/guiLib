#include "Button.h"
#include <FontManager.h>
#include <MainWindow.h>


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
    m_label(new Label(text,MainWindow::displayWidth(), this))
{
    m_backgroundFill = false;
    m_borderWidth = 3;
    uint32_t w = m_label->width();
    uint32_t h = m_label->height();
    m_label->setAlignment(GObject::CenterIn);
    setSizes(w+borderWidth()*2+2, h+m_borderWidth*2+2);
    updateBuffer();
    redraw();
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


