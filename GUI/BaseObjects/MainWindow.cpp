#include "MainWindow.h"
#include <Buffer.h>
#include <DisplayManagerDebug.h>

using Display::Buffer;

Display::DisplayManagerDebug MainWindow::m_displayManager(256,0,true);
int MainWindow::m_objCounter = 0;

void testFunction(){
    std::cout << "test timer function" << '\n';
}

MainWindow::MainWindow() :
    GObject(nullptr)
{
    if (m_objCounter != 0)
        return;
    m_objectBuffer = new Buffer(m_displayManager.displayWidth(), m_displayManager.displayHeight());
    setSizes(m_displayManager.displayWidth(), m_displayManager.displayHeight());
    m_objCounter = 1;
    startTimer(testFunction, 1000);
}

MainWindow::~MainWindow(){

}

void MainWindow::redraw(){
    for (auto child : children()){
        m_objectBuffer->mergeData(child->buffer(), child->x(), child->y());
    }
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
