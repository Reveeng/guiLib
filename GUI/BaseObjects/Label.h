#ifndef LABEL_H
#define LABEL_H

#include <GObject.h>
#include <Buffers/MI12864/LabelBuffer.h>

class Label : public GObject
{
public:
    Label(GObject *parent = nullptr);
    Label(const std::string &text,const std::string &fontName = "", GObject *parent = nullptr);
//    Label(const )

    ~Label();

    void changeFont(const std::string &fontName);
    std::string fontName() const;

    void setText(const std::string &t);
    std::string text() const;

protected:

    virtual void updateBuffer();

private:
    std::string m_fontName;
//    Display::MI12864::LabelBuffer m_buffer;
};

#endif // LABEL_H
