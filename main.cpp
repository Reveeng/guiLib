#include <iostream>
using namespace std;


#include <cstring>
#include <FontManager.h>

#include <Fonts/MI12864/FontData.h>
#include <Fonts/MI12864/font_small.h>

#include <Buffers/MI12864/Buffer.h>
#include <Buffers/MI12864/LabelBuffer.h>

#include <Rectangle.h>
#include <Label.h>
#include <MainEventLoop.h>
#include <MainWindow.h>

using namespace Display;
using namespace Display::MI12864;

#include <atomic>
#include <thread>
#include <csignal>
#include <functional>

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

//    Rectangle rect(0,0, 20,20, &window);
//    rect.setFillBackground(false);

//    rect.setBorderWidth(0);

    Label lbl("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA","small", &window);
    lbl.setPosition(0,0);
    //    lbl.setAlignment(GObject::CenterIn);


//    lbl.setPosition(5,5);

    int xs[] = {0,10,15,20};
    int ys[] = {0,5,10,15};
    int counter = 0;
    while (!stopFlag.load()){
         std::this_thread::sleep_for(std::chrono::milliseconds(500));
        int x = xs[counter];
        int y = ys[counter];
//        rect.setPosition(x,y);
        counter = counter+1 == 4 ? 0 : counter+1;
    }

    return 0;
}

