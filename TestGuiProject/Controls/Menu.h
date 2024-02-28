#ifndef MENU_H
#define MENU_H

#include <GObject.h>
#include <Button.h>

//class ButtonVector : public std::vector<Button *>
//{
//public:
//    void addFew(uint32_t c);
//    void removeFew(uint32_t c);
//};

class Menu : public Rectangle
{
public:
    Menu(uint32_t btnHeight, uint32_t spacing,GObject *parent);
    ~Menu();

//    template
    void addButton(const std::string &text);
protected:
    virtual void updateBuffer() override;
private:
    void initFunctions();
    void rectChanged(Rect rect);

    uint32_t m_btnHeight;
    uint32_t m_spacing;

    uint32_t m_maxVisibleBtns;

    uint32_t m_currentPosition;
    std::vector<Button *> m_btns;
};

#endif // MENU_H
