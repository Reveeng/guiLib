#include "PlainText.h"
#include <FontManager.h>
#include <FontData.h>
#include <Buffer.h>

using Display::LabelBuffer;
using Display::Abstraction::AbstractFrameBuffer;

PlainText::PlainText(GObject *p) :
    GObject(p),
    m_cursorPosition(0),
    m_fontName(FontManager::getDefaultFontName())
{
    initFunction();
    createTriangles();
}

PlainText::PlainText(uint32_t w, uint32_t h, GObject *p):
    GObject(0,0,w,h,p),
    m_cursorPosition(0),
    m_fontName(FontManager::getDefaultFontName())
{
    m_sData.setMaxWidth(width()/FontManager::getFontData(m_fontName)->symbolWidth());
    initFunction();
    createTriangles();
    calculateLineCount();
}

PlainText::~PlainText()
{

}

void PlainText::setText(const std::string &data)
{
    call_setter(m_data,data);
}

void PlainText::setFont(const std::string &fontName)
{
    call_setter(m_fontName,fontName);
}

void PlainText::increaseCursorPosition()
{
    uint32_t pos = call_getter(m_cursorPosition)+1;
    call_setter(m_cursorPosition,pos);
}

void PlainText::decreaseCursorPosition()
{
    uint32_t pos = call_getter(m_cursorPosition)-1;
    call_setter(m_cursorPosition,pos);
}

void PlainText::updateBuffer()
{
    m_upTr->setVisible(m_cursorPosition != 0);
    m_downTr->setVisible(m_cursorPosition+1 != m_sData.linesSize()-m_lines.size());
    uint32_t ypos = m_upTr->height()+1;
    const Display::FontData * d = FontManager::getFontData(m_fontName);
    for (auto l : m_lines){
        m_objectBuffer->mergeData(dynamic_cast<AbstractFrameBuffer*>(l),0,ypos);
        ypos += d->symbolHeight();
    }
    GObject::updateBuffer();
}

void PlainText::textChanged(std::string text)
{
    m_sData.setData(text);
    Display::Buffer * b = dynamic_cast<Display::Buffer*>(m_objectBuffer);
    b->clearBuffer();
    clear();
    setDataToBuffers();
    updateBuffer();
    redraw();
}

void PlainText::fontChanged(std::string fontName)
{
    (void)fontName;
    m_sData.setMaxWidth(width()/FontManager::getFontData(m_fontName)->symbolWidth());
    calculateLineCount();
    setDataToBuffers();
    Display::Buffer * b = dynamic_cast<Display::Buffer*>(m_objectBuffer);
    b->clearBuffer();
    clear();
    updateBuffer();
    redraw();
}

void PlainText::cursorPositionChanged(uint32_t pos)
{
    if (m_sData.linesSize()-pos <= m_lines.size())
    {
        m_cursorPosition = pos-1;
        return;
    }
    setDataToBuffers();
    Display::Buffer * b = dynamic_cast<Display::Buffer*>(m_objectBuffer);
    b->clearBuffer();
    clear();
    updateBuffer();
    redraw();
}

void PlainText::rectChanged(Rect rect)
{
    (void)rect;
    calculateLineCount();
    setDataToBuffers();
    Display::Buffer * b = dynamic_cast<Display::Buffer*>(m_objectBuffer);
    b->clearBuffer();
    clear();
    updateBuffer();
    redraw();
}

void PlainText::initFunction()
{
    m_objectBuffer = new Display::Buffer(width(), height());
    declare_setter_getter(m_data);
    declare_setter_getter(m_fontName);
    declare_setter_getter(m_cursorPosition);

    connect("rect",&PlainText::rectChanged, this);
    bind_callback(m_data, &PlainText::textChanged);
    bind_callback(m_fontName, &PlainText::fontChanged);
    bind_callback(m_cursorPosition, &PlainText::cursorPositionChanged);
}

void PlainText::createTriangles()
{
    m_upTr = new UpTriangle(this);
    m_downTr = new DownTriangle(this);

    m_upTr->setAlignment(GObject::HCenter);
    m_upTr->setAnchor(Top,this,Top,0);

    m_downTr->setAlignment(GObject::HCenter);
    m_downTr->setAnchor(Bottom,this,Bottom,0);
}

void PlainText::calculateLineCount()
{
    const Display::FontData *d = FontManager::getFontData(m_fontName);
    Rect rect = rectangle();
    uint32_t contentItemHeight = rect.h-m_upTr->height()-m_downTr->height();
    uint32_t lineCount = contentItemHeight/d->symbolHeight();
    if (lineCount == m_lines.size())
        return;
    if (lineCount < m_lines.size()){
        m_lines.removeLastFew(m_lines.size()-lineCount);
    }else{
        m_lines.createFew(lineCount-m_lines.size());
    }
    updateLinesProperty();
}

void PlainText::updateLinesProperty()
{
    Rect rect = rectangle();
    uint32_t maxWidth = rect.w;
    const Display::FontData * d = FontManager::getFontData(m_fontName);
    for (uint32_t i = 0; i < m_lines.size(); ++i)
    {
        LabelBuffer* b = m_lines[i];
        b->setMaximumWidth(maxWidth);
        b->setFont(d);
    }

}

void PlainText::setDataToBuffers()
{
    uint32_t stLineIndex = m_cursorPosition;
    uint32_t labelSize = m_lines.size();
    for (uint32_t c = 0; c < labelSize; ++c){
        std::string line = m_sData.getLine(stLineIndex);
        if (line[0] == '\n')
            line.erase(0,1);
        m_lines[c]->setLabelData(line);
        stLineIndex++;
    }
}



void VectorLabel::removeLastFew(uint32_t c)
{
    auto re = rend();
    for (uint32_t i = c; i != 0 ; --i){
        delete *re;
        re--;
    }
    erase(end()-c, end());
}

void VectorLabel::createFew(uint32_t c)
{
    for (uint32_t i = 0; i < c; i++){
        LabelBuffer *label = new LabelBuffer();
        push_back(label);
    }
}

SplitData::SplitData()
{

}

SplitData::SplitData(const std::string &data, uint32_t mw):
    m_maxWidth(mw),
    m_data(data)
{
    calculatePositions();
}

void SplitData::setMaxWidth(uint32_t w)
{
    m_maxWidth = w;
    m_delPositions.clear();
    calculatePositions();
}

void SplitData::setData(const std::string &data)
{
    m_data = data;
    m_delPositions.clear();
    calculatePositions();
}

uint32_t SplitData::linesSize() const
{
    return m_delPositions.size();
}

std::string SplitData::getLine(uint32_t index)
{
    if (index > m_delPositions.size()-1)
        return "";
    std::size_t stPos = index == 0 ? 0 : m_delPositions[index-1];
    std::size_t endPos = index == m_delPositions.size()-1 ? m_delPositions[index]+1 : m_delPositions[index];
    return m_data.substr(stPos,endPos-stPos);
}

void SplitData::calculatePositions()
{
    std::size_t pos = 0;
    std::size_t maxw = m_data.size() > m_maxWidth ? m_maxWidth : m_data.size();
    for (std::size_t i = 0; i < m_data.size(); ++i){
        if (m_data[i] == '\n' || i-pos >= maxw){
            m_delPositions.push_back(i);
            pos = i;
        }
        if (i == m_data.size()-1)
            m_delPositions.push_back(i);
    }
}
