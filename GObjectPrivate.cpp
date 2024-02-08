#include "GObjectPrivate.h"
#include <utility>

GObjectPrivate::GObjectPrivate():
    pos(0,0,0,0),
    visible(false),
    highlight(false)
{

}

GObjectPrivate::GObjectPrivate(GObjectPrivate &o):
    pos(o.pos),
    visible(o.visible),
    highlight(o.highlight)
{

}

//GObjectPrivate::GObjectPrivate(GObjectPrivate &&o):
//    pos(std::move(o.pos)),
//    visible(std::move(o.visible)),
//    highlight(std::move(o.highlight))
//{

//}
