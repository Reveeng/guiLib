#ifndef FONTMANAGER_H
#define FONTMANAGER_H

//#include <AbstractFontContainer.h>
#include <Fonts/MI12864/FontData.h>
#include <string>
#include <map>

namespace Display {
    using Abstraction::AbstractFontContainer;
    using MI12864::FontData;
    class FontManager
    {
    public:
        FontManager(FontManager&) = delete;
        FontManager(FontManager&&) = delete;


        ~FontManager();

        static void registerFont(const std::string &key,const FontData &data);
        static const FontData *getFontData(const std::string &key);
        static const FontData *getDefaultFont();
        static void setDefaultFont(const std::string &key);

    private:
        FontManager();
        static FontManager& getInstance();
        std::string m_defaultKey;
        std::map<std::string, FontData> m_fontMap;
    };
}

#endif // FONTMANAGER_H
