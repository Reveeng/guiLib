#ifndef BUTTON_H
#define BUTTON_H

#include <Rectangle.h>
#include <Label.h>


class Button : public Rectangle
{
public:
    Button(GObject * p);
    Button(const std::string &text, GObject *p);

    void setText(const std::string &text);
    std::string text() const;

    void setFocused(bool f);
//    bool focused() const;


protected:
    Label *contentItem();

private:
//    std::atomic<bool> m_focused;
    Label *m_label;
};

#endif // BUTTON_H
