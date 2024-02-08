#include "MainEventLoop.h"

MainEventLoop::MainEventLoop()
{

}

void MainEventLoop::start()
{
    getInstance().EventLoop::start();
}

void MainEventLoop::stop()
{
    getInstance().EventLoop::stop();
}

std::thread::id MainEventLoop::mainThreadId()
{
    return getInstance().EventLoop::eventLoopThredId();
}

//void MainEventLoop::pushEvent(Event *ev)
//{
//    getInstance().EventLoop::pushEvent(ev);
//}

MainEventLoop &MainEventLoop::getInstance()
{
    static MainEventLoop loop;
    return loop;
}

MainEventLoop *MainEventLoop::getPointer()
{
    return &getInstance();
}
