#ifndef LABEL_H
#define LABEL_H

#include <GObject.h>
#include <LabelBuffer.h>

class Label : public GObject
{
public:
    Label(GObject *parent);
    Label(const std::string &text,GObject *p);
    Label(const std::string &text,const std::string &fontName = "", GObject *parent = nullptr);
    Label(const std::string &text,uint32_t mWidth, GObject *p);

    ~Label();

    void changeFont(const std::string &fontName);
    std::string fontName() const;

    void setText(const std::string &t);
    std::string text() const;

protected:

    virtual void updateBuffer() override;
    virtual void calculatePosition() override;

private:
    bool m_fixedSize;
    std::string m_fontName;
};

#endif // LABEL_H
