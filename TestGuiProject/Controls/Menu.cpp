#include "Menu.h"
#include <Button.h>
#include <Buffer.h>

Menu::Menu(uint32_t btnHeight, uint32_t spacing,GObject *parent):
    Rectangle(parent),
    m_btnHeight(btnHeight),
    m_spacing(spacing),
    m_maxVisibleBtns(0),
    m_currentPosition(0)
{
    m_backgroundFill = false;
    m_borderWidth = 0;
}

Menu::~Menu()
{

}

void Menu::initFunctions()
{
    bind_callback("rect", &Menu::rectChanged);
}

void Menu::rectChanged(Rect rect)
{
    m_maxVisibleBtns = rect.h/(m_btnHeight+m_spacing);
}

void Menu::updateBuffer()
{
//    Button *fbtn = m_btns.front();
//    if (m_currentPosition > m_maxVisibleBtns)
//    {
//        fbtn->setY();
//    }
//    for (uint32_t i = m_currentPosition; i < m_currentPosition+m_maxVisibleBtns)
}

void Menu::addButton(const std::string &text)
{
    Button *b = new Button(text, this);
    b->setAlignment(GObject::HCenter);

    if (m_btns.size() != 0)
    {
        Button *pbtn = m_btns.back();
        b->setAnchor(Top,pbtn,Bottom,m_spacing);
    }
    m_btns.push_back(b);
    clear();
    updateBuffer();
    redraw();
}

//void ButtonVector::addFew(uint32_t c)
//{
//    for (uint32_t i = 0; i < c; ++i){
//        Button * nbtn = new Button();
//    }
//}

//void ButtonVector::removeFew(uint32_t c)
//{

//}
