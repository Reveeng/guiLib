#include "MenuButton.h"

MenuButton::MenuButton(GObject * parent):
    m_button(new Button(parent)),
    m_check(new CheckIcon(parent))
{
    m_button->setAlignment(GObject::HCenter);
    m_check->setAnchor(Right,m_button, Left,4);
}

void MenuButton::setButtonData(MenuButtonData *data)
{
    m_curData = data;
}

void MenuButton::clicked()
{
    if (m_curData)
        m_curData->m_callback();
}
