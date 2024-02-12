#include <iostream>

#include <cstring>
#include <FontManager.h>

#include <FontData.h>
#include <font_small.h>

//#include <Rectangle.h>
//#include <Label.h>
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

int Testfunction(){
    return 2;
}

int main()
{
    signal(SIGINT,systemSignalProccess);
    signal(SIGTERM,systemSignalProccess);

    FontManager::registerFont("small", font_small());
    FontManager::setDefaultFont("small");

    MainWindow window;

    Button *btn = new Button("Test",&window);
    btn->setSizes(50,20);
    btn->setAlignment(GObject::CenterIn);

    bool check = true;
    while (!stopFlag.load()){
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        btn->setFocused(check);
        check = !check;
    }

    return 0;
}

