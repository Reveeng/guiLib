#include "MainWindow.h"
#include <Buffer.h>
#include <DisplayManagerDebug.h>
#include <MainEventLoop.h>

#include <iostream>
using Display::Buffer;


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
