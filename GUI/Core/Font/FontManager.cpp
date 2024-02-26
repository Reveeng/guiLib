#include "FontManager.h"
#include <cstring>

using Display::FontData;

FontManager::FontManager()
{

}

FontManager::~FontManager()
{

}

void FontManager::registerFont(const std::string &key, const FontData &data)
{
    FontManager &manager = getInstance();
    manager.m_fontMap[key] = data;
}

const FontData *FontManager::getFontData(const std::string &key)
{
    FontManager &manager = getInstance();
    auto iter = manager.m_fontMap.find(key);
    if (iter == manager.m_fontMap.end())
        return nullptr;
    return &(iter->second);
}

const FontData *FontManager::getDefaultFont()
{
    FontManager &manager = getInstance();
    return getFontData(manager.m_defaultKey);
}

const std::string &FontManager::getDefaultFontName()
{
    FontManager &manager = getInstance();
    return manager.m_defaultKey;
}

void FontManager::setDefaultFont(const std::string &key)
{
    FontManager &manager = getInstance();
    manager.m_defaultKey = key;
}

FontManager &FontManager::getInstance()
{
    static FontManager manager;
    return manager;
}
