#include "AbstractClassPrivate.h"

AbstractClassPrivate::AbstractClassPrivate(AbstractClassPrivate *p):
    m_parent(p)
{
    m_objectEventLoop = m_parent ? p->m_objectEventLoop : std::make_shared<EventLoop>();
    if (!m_parent)
        m_objectEventLoop->start();
}


AbstractClassPrivate::~AbstractClassPrivate()
{

}

bool AbstractClassPrivate::isCalledFromObjectThread() const
{
    return std::this_thread::get_id() == m_objectEventLoop->eventLoopThredId();
}

AbstractClassPrivate *AbstractClassPrivate::parent() const
{
    return m_parent;
}

std::shared_ptr<EventLoop> AbstractClassPrivate::eventLoop() const
{
    return m_objectEventLoop;
}
