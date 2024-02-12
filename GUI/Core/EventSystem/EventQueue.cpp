#include "EventQueue.h"
#include <unistd.h>
#include <sys/select.h>
#include <iostream>

EventQueue::EventQueue():
    m_dropWaitReadFd(-1),
    m_dropWaitWriteFd(-1)
{
    int fds[] = {-1,-1};
    ::pipe(fds);
    m_dropWaitReadFd = fds[0];
    m_dropWaitWriteFd = fds[1];
}

void EventQueue::waitEvent()
{
    fd_set fds_to_check, rdfs;
    int ndfs = 0;
    FD_ZERO(&fds_to_check);
    FD_SET(m_dropWaitReadFd, &fds_to_check);
    ndfs = m_dropWaitReadFd+1;
    int ret = 0;
    while(ret <= 0){
        rdfs = fds_to_check;
        ret = ::select(ndfs+1,&rdfs, NULL,NULL,NULL);
    }
}

void EventQueue::breakWait()
{
    if (m_dropWaitWriteFd <= 0)
        return;
    ::write(m_dropWaitWriteFd,"E\r\n",3);
}

void EventQueue::getEvents(std::vector<AbstractEvent *> &cont)
{
    std::lock_guard<std::mutex> g(m_dataMutex);
    m_events.swap(cont);
}


