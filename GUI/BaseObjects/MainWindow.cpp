#include "MainWindow.h"
#include <Buffers/MI12864/Buffer.h>
#include <Backends/CLI/DisplayManager.h>
#include <MainEventLoop.h>

#include <iostream>
using Display::MI12864::Buffer;

static void timerFunc(){
    std::cout << "Test timer" << '\n';
}

MainWindow::MainWindow() :
    GObject(nullptr),
    m_displayManager(256,0,true)
{
    m_objectBuffer = new Buffer(m_displayManager.displayWidth(), m_displayManager.displayHeight());
    setSizes(m_displayManager.displayWidth(), m_displayManager.displayHeight());
    MainEventLoop::start();
    m_objectEventLoop = MainEventLoop::getPointer();
    m_timerId = startTimer(std::bind(timerFunc), 1000);
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
