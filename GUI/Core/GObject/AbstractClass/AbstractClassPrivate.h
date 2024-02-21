#ifndef ABSTRACTCLASSPRIVATE_H
#define ABSTRACTCLASSPRIVATE_H

#include <EventLoop.h>
#include <memory>

class AbstractClassPrivate
{
public:
    AbstractClassPrivate(AbstractClassPrivate *parent = nullptr);
    virtual ~AbstractClassPrivate();

    bool isCalledFromObjectThread() const;
    AbstractClassPrivate *parent() const;
    std::shared_ptr<EventLoop> eventLoop() const;

protected:
    AbstractClassPrivate *m_parent;

    std::shared_ptr<EventLoop> m_objectEventLoop;
};

#endif // ABSTRACTCLASSPRIVATE_H
