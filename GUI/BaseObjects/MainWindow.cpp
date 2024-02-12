#include "MainWindow.h"
#include <Buffer.h>
#include <DisplayManagerDebug.h>
#include <MainEventLoop.h>

using Display::Buffer;

Display::DisplayManagerDebug MainWindow::m_displayManager(256,0,true);
int MainWindow::m_objCounter = 0;

MainWindow::MainWindow() :
    GObject(nullptr)
{
    if (m_objCounter != 0)
        return;
    m_objectBuffer = new Buffer(m_displayManager.displayWidth(), m_displayManager.displayHeight());
    setSizes(m_displayManager.displayWidth(), m_displayManager.displayHeight());
    MainEventLoop::start();
    m_objectEventLoop = MainEventLoop::getPointer();
    m_objCounter = 1;
}

MainWindow::~MainWindow(){
    MainEventLoop::stop();
}

void MainWindow::redraw(){
    m_displayManager.drawBuffer(m_objectBuffer);
}

void MainWindow::updateBuffer(){

}

uint32_t MainWindow::displayWidth()
{
    return m_displayManager.displayWidth();
}

uint32_t MainWindow::displayHeight()
{
    return m_displayManager.displayHeight();
}
