#ifndef GOBJECTPRIVATE_H
#define GOBJECTPRIVATE_H

#include <Position.h>
#include <mutex>

class GObjectPrivate
{
public:
    GObjectPrivate();
    GObjectPrivate(GObjectPrivate &o);
    Position pos();
    bool visible();

private:
    std::mutex m_dataMutex;
    Position m_pos;
    bool m_visible;
    bool m_highlight;
};

#endif // GOBJECTPRIVATE_H
