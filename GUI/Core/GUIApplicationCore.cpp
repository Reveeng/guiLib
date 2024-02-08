#include "GUIApplicationCore.h"

#include <MainEventLoop.h>
#include <DrawBackend.h>

Display::DrawBackend GUIApplicationCore::m_backend;

GUIApplicationCore::GUIApplicationCore(Display::DrawBackend &backend)
{
    m_backend = backend;
    MainEventLoop::start();
}

GUIApplicationCore::~GUIApplicationCore()
{
    MainEventLoop::stop();
}

Display::DrawBackend *GUIApplicationCore::backend(){
    return &m_backend;
}
