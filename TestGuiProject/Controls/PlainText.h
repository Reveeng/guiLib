#ifndef PLAINTEXT_H
#define PLAINTEXT_H

#include <LabelBuffer.h>
#include <GObject.h>
#include <UpTriangle.h>
#include <DownTriangle.h>

class VectorLabel : public std::vector<Display::LabelBuffer*>
{
public:
    void removeLastFew(uint32_t c);
    void createFew(uint32_t c);
};

class SplitData
{
public:
    SplitData();
    SplitData(const std::string &data, uint32_t mw);

    void setMaxWidth(uint32_t w);
    void setData(const std::string &data);
    uint32_t linesSize() const;
    std::string getLine(uint32_t index);

private:
    void calculatePositions();
    uint32_t m_maxWidth;
    std::string m_data;
    std::vector<uint32_t> m_delPositions;
};


class PlainText : public GObject
{
public:
    PlainText(GObject *parent = nullptr);
    PlainText(uint32_t w, uint32_t h, GObject *parent = nullptr);
    ~PlainText();


    void setText(const std::string &data);
    void setFont(const std::string &fontName);

    void increaseCursorPosition();
    void decreaseCursorPosition();

    virtual void updateBuffer() override final;

protected:
    void textChanged(std::string text);
    void fontChanged(std::string fontName);
    void cursorPositionChanged(uint32_t pos);
    void rectChanged(Rect rect);

private:
    void initFunction();
    void createTriangles();

    void calculateLineCount();
    void updateLinesProperty();
    void setDataToBuffers();

    UpTriangle *m_upTr;
    DownTriangle *m_downTr;

    uint32_t m_cursorPosition;

    std::string m_data;
    SplitData m_sData;
    std::string m_fontName;
    VectorLabel m_lines;
};

#endif // PLAINTEXT_H
