#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <GObject.h>
#include <DisplayManagerDebug.h>
//using Display::CLI::DisplayManager;

class MainWindow : public GObject
{
public:
    MainWindow();
    ~MainWindow();

    virtual void redraw() override;
    virtual void updateBuffer() override final;


private:
    uint32_t m_timerId;
    Display::DisplayManagerDebug m_displayManager;
    static int m_objCounter;
};

#endif // MAINWINDOW_H
