#include "AbstractObject.h"

AbstractObject::AbstractObject()
{

}

void AbstractObject::declare_setter(const std::string &key,std::function<void ()> f)
{
    m_setters[key] = f;
}
