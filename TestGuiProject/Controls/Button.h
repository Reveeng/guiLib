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
    bool focused();

    void setTextAlignment(Alignment al);


protected:
    void focusedChangedCallback(bool f);
    Label *contentItem();

private:
    void calculateSize();
    bool m_focused;
    Label *m_label;
};

#endif // BUTTON_H
