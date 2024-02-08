#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <GObject.h>
#include <Backends/CLI/DisplayManager.h>
using Display::CLI::DisplayManager;

class MainWindow : public GObject
{
public:
    MainWindow();
    ~MainWindow();

    virtual void draw(bool force = false) override;
    virtual void updateBuffer() override final;


private:
    DisplayManager m_displayManager;
    static int m_objCounter;
};

#endif // MAINWINDOW_H
