#ifndef ABSTRACTOBJECT_H
#define ABSTRACTOBJECT_H

#include <functional>

//class AbstractInvoker{
//public:
//    virtual ~AbstractInvoker(){}
//    virtual void invoke() = 0;
//};

//template <typename Result, typename ...Args>
//class TemplateInvoker : AbstractInvoker{
//public:
//    TemplateInvoker(std::function<Result(Args...)> f):
//        AbstractInvoker(),
//        m_functor(f)
//    {

//    }
//    ~AbstractInvoker(){}
//    virtual void invoke() override {
//        m_functor();
//    }

//private:
//    std::function<Result(Args...)> m_functor;
//};

#include <iostream>

#include <map>
//template <typename ...Args>
//void invokeSetter(std::function<void(Args...)> f,Args... args){
//    std::cout << "common thing" << '\n';
//    f(std::forward<Args>(args)...);
//}

class AbstractObject
{
public:
    AbstractObject();
    void declare_setter(const std::string &name,std::function<void()> f);
    void declare_getter(std::function<void()> f);

    template <typename ...Args>
    void invokeSetter(const std::string &name,Args... args){
        m_setters.
    }

//    void protectSetter(std::function<void()> f);
//    void
private:
    std::map<std::string, std::function<void()>> m_setters;
};

#endif // ABSTRACTOBJECT_H
