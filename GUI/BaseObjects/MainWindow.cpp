#include "MainWindow.h"
#include <Buffers/MI12864/Buffer.h>
#include <Backends/CLI/DisplayManager.h>
#include <MainEventLoop.h>

using Display::MI12864::Buffer;

MainWindow::MainWindow() :
    GObject(nullptr),
    m_displayManager(256,0,true)
{
    m_objectBuffer = new Buffer(m_displayManager.displayWidth(), m_displayManager.displayHeight());
    setSizes(m_displayManager.displayWidth(), m_displayManager.displayHeight());
    MainEventLoop::start();
    m_objectEventLoop = MainEventLoop::getPointer();
}

MainWindow::~MainWindow(){
    MainEventLoop::stop();
}

void MainWindow::draw(bool force){
    (void)force;
    m_displayManager.drawBuffer(m_objectBuffer);
}

void MainWindow::updateBuffer(){

}
