#include <iostream>

#include <cstring>
#include <FontManager.h>

#include <FontData.h>
#include <font_small.h>

#include <MainWindow.h>

using namespace std;
using namespace Display;




#include <atomic>
#include <thread>
#include <csignal>
#include <functional>

#include <Button.h>
#include <PlainText.h>

//#include <UpTriangle.h>
//#include <DownTriangle.h>
//#include <CheckIcon.h>

#include <Menu.h>

static std::atomic<bool> stopFlag(false);


void systemSignalProccess(int sig)
{
    if (sig == SIGINT || sig == SIGABRT){
        stopFlag.store(true);
    }
}

enum Enum{
    AA,
    BB
};

int Testfunction(){
    return 2;
}

int main()
{
    signal(SIGINT,systemSignalProccess);
    signal(SIGTERM,systemSignalProccess);

    FontManager::registerFont("small", font_small());
    FontManager::setDefaultFont("small");

    MainWindow *window = new MainWindow();

    Menu *menu =  new Menu(10,2,window);
    menu->setWidth(window->width());
    menu->setAnchor(Top,window,Top,7);
    menu->setAnchor(Bottom, window,Bottom, 5);

    menu->addButton("AA");
    menu->addButton("BB");

    while (!stopFlag.load()){
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    window->deleteLater();

    return 0;
}

