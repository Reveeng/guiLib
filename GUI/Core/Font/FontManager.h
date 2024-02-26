#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include <FontData.h>
#include <string>
#include <map>

class FontManager
{
public:
    FontManager(FontManager&) = delete;
    FontManager(FontManager&&) = delete;


    ~FontManager();

    static void registerFont(const std::string &key,const Display::FontData &data);
    static const Display::FontData *getFontData(const std::string &key);
    static const Display::FontData *getDefaultFont();
    static const std::string &getDefaultFontName();
    static void setDefaultFont(const std::string &key);

private:
    FontManager();
    static FontManager& getInstance();
    std::string m_defaultKey;
    std::map<std::string, Display::FontData> m_fontMap;
};

#endif // FONTMANAGER_H
