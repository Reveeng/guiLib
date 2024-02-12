#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <GObject.h>
#include <DisplayManagerDebug.h>

class MainWindow : public GObject
{
public:
    MainWindow();
    ~MainWindow();

    virtual void redraw() override;
    virtual void updateBuffer() override final;

    static uint32_t displayWidth();
    static uint32_t displayHeight();

private:
    uint32_t m_timerId;
    static Display::DisplayManagerDebug m_displayManager;
    static int m_objCounter;
};

#endif // MAINWINDOW_H
