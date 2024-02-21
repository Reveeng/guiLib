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
//    Rectangle * rect = new Rectangle(0,2,10,10, &window);
//    rect->setPosition(10,10);


    Button *btn = new Button("Test",window);
    btn->setAlignment(GObject::HCenter);
    btn->setAnchor(Top,window,Top,5);

    Button *sbtn = new Button("Test2",window);
    sbtn->setAlignment(GObject::HCenter);
    sbtn->setAnchor(Top,btn, Bottom,4);

    btn->deleteLater();
    while (!stopFlag.load()){
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
//        btn->setFocused(true);
    }
    window->deleteLater();
//    delete btn;
//    delete sbtn;

    return 0;
}

