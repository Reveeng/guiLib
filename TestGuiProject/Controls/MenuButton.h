#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include <Button.h>
#include <CheckIcon.h>
#include <functional>

class MenuButtonData
{
public:
    MenuButtonData(std::string t,
                   std::function<bool()> chF,
                   std::function<void()> f):
        m_btnText(t),
        m_checkF(chF),
        m_callback(f)
    {

    }
    ~MenuButtonData()
    {

    }

    bool isChecked()
    {
        return m_checkF();
    }
private:
    std::string m_btnText;
    std::function<bool()> m_checkF;
    std::function<void()> m_callback;

    friend class MenuButton;
};

class MenuButton
{
public:
    MenuButton(GObject *parent);

    void setButtonData(MenuButtonData *data);


private:
    void clicked();

    MenuButtonData *m_curData;
    Button * m_button;
    CheckIcon * m_check;
};

#endif // MENUBUTTON_H
