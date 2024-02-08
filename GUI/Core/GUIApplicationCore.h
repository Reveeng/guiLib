#ifndef GUIAPPLICATIONCORE_H
#define GUIAPPLICATIONCORE_H

#include <MainEventLoop.h>
#include <DrawBackend.h>

class GUIApplicationCore
{
public:
    GUIApplicationCore(Display::DrawBackend &backend);
    ~GUIApplicationCore();

    static Display::DrawBackend *backend();

private:
    static Display::DrawBackend m_backend;
};

#endif // GUIAPPLICATIONCORE_H
