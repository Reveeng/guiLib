#ifndef MAINEVENTLOOP_H
#define MAINEVENTLOOP_H

#include <EventLoop.h>

class MainEventLoop : public EventLoop
{
public:
    MainEventLoop(MainEventLoop&) = delete;
    MainEventLoop(MainEventLoop&&) = delete;

    static void start();
    static void stop();
    static std::thread::id mainThreadId();

    template <class T>
    static void pushEvent(T &ev){
        getInstance().EventQueue::pushEvent(ev);
    }
    static MainEventLoop *getPointer();

private:
    static MainEventLoop& getInstance();

    MainEventLoop();
    friend class GObject;
};

#endif // MAINEVENTLOOP_H
