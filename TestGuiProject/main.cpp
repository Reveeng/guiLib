#include <iostream>

#include <cstring>
#include <FontManager.h>

#include <FontData.h>
#include <font_small.h>

#include <Rectangle.h>
#include <Label.h>
#include <MainWindow.h>

using namespace std;
using namespace Display;




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

    Rectangle *rect = new Rectangle(0,0, 20,20, &window);
    rect->setFillBackground(false);
    rect->setBorderWidth(3);

//    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    Rectangle *rect2 =  new Rectangle(&window);
    rect2->setAnchor<Right,Right>(&window,4);
    rect2->setSizes(10,10);


    Label *label =  new Label(&window);
    label->setAnchor<Top,Bottom>(rect,3);
    label->setText("AGA");

//    label.setAnchor<Right,Right>(&window,4);


//    label.setAnchor<Top,Bottom>(&rect2,3);

//    int xs[] = {0,10,15,20};
//    int ys[] = {0,5,10,15};
//    int counter = 0;
    while (!stopFlag.load()){
         std::this_thread::sleep_for(std::chrono::milliseconds(500));
//        int x = xs[counter];
//        int y = ys[counter];
//        rect.setPosition(x,y);
//        counter = counter+1 == 4 ? 0 : counter+1;
    }

    return 0;
}

