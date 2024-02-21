#ifndef ABSTRACTCLASS_H
#define ABSTRACTCLASS_H


#include <functional>
#include <type_traits>
#include <AbstractClassPrivate.h>
#include <invokable.h>
#include <ThreadSafeMap.h>

#include <iostream>

class AbstractClass : public AbstractClassPrivate
{
public:
    AbstractClass(AbstractClass *parent = nullptr):
        AbstractClassPrivate(parent),
        m_this(this)
    {
        createObjectSetter("aboutToDelete", m_this);
    }
    ~AbstractClass()
    {
        for (auto &pair : m_setterMap){
            delete pair.second;
        }
        for (auto &pair : m_getterMap){
            delete pair.second;
        }
        for (auto sender : m_senders){
            sender->disconnect(this);
        }
    }

    AbstractClass *parent(){return dynamic_cast<AbstractClass*>(m_parent);}
    void deleteLater()
    {
        invokeSignal<AbstractClass*>("aboutToDelete");
        auto f = std::bind(&AbstractClass::__delete, this);
        Event<> ev(f);
        m_objectEventLoop->pushEvent(ev);
    };

    template<class RecObject, typename ...Args>
    static void connect(AbstractClass *sp, const std::string &key, RecObject *cp, void(RecObject::*f)(Args...))
    {
      sp->connect(key,f,cp);
    }

    template<typename ...Args>
    static void connect(AbstractClass *sp, const std::string &key, void (*f)(Args...))
    {
        sp->connect(key,f);
    }

    template<typename F, typename ...Args>
    static void connect(AbstractClass *sp,const std::string &key, F f)
    {
        sp->connect(key,f);
    }


protected:
    template <typename ...Args>
    void createObjectSetter(const std::string &key, Args&... args){
        Setter<Args...> *connector = new Setter(args...);
        m_setterMap[key] = dynamic_cast<AbstractSetterCallable*>(connector);
    }

    template <typename T, std::enable_if_t<std::is_constructible_v<T>, bool> = true>
    void createObjectGetter(const std::string &key, T& objP)
    {
        Getter<T> *get = new Getter<T>(objP);
        m_getterMap[key] = dynamic_cast<AbstractGetterCallable*>(get);
    }

    template <typename ...Args>
    void invokeSetter(const std::string &key, const Args&... args){
        AbstractSetterCallable *sc = m_setterMap[key];
        Setter<Args...> *setter = dynamic_cast<Setter<Args...> *>(sc);
        if (!sc)
            return;
        if (isCalledFromObjectThread()){
            setter->invoke(args...);
            return;
        }
        auto tp = std::make_tuple(args...);
        auto evF = bindHelper(&Setter<Args...>::invoke, setter,
                            tp, std::make_index_sequence<sizeof...(Args)>{});
        Event<> ev(evF);
        m_objectEventLoop->pushEvent(ev);
    }
    template <typename ...Args>
    void invokeSignal(const std::string &key)
    {
        AbstractSetterCallable *sc = m_setterMap[key];
        Setter<Args...> *setter = dynamic_cast<Setter<Args...> *>(sc);
        setter->invokeSignal();
    }

    //cant
    template <typename T,std::enable_if_t<std::is_constructible_v<T>, bool> = true>
    T invokeGetter(const std::string &key) const{
        AbstractGetterCallable *get = m_getterMap[key];
        Getter<T> *getter = dynamic_cast<Getter<T>*>(get);
        if (!getter){
            T t;
            return t;
        }
        if (isCalledFromObjectThread())
            return getter->invoke();

        auto f = std::bind(&Getter<T>::invoke,getter);
        WaitableEvent<T> ev(f);
        m_objectEventLoop->pushEvent(ev);
        return ev.waitEventExecution();
    }

    template<class RecObject, typename ...Args,
             std::enable_if_t<std::is_base_of_v<AbstractClass,RecObject>,bool> = true>
    void connect(const std::string &key, void(RecObject::*f)(Args...),RecObject *o){
        AbstractSetterCallable *sc = m_setterMap[key];
        Setter<Args...> *setter = dynamic_cast<Setter<Args...> *>(sc);
        if (!setter)
          return;
        auto subt = subtuple(m_placeholders,std::make_index_sequence<sizeof...(Args)>{});
        std::function<void(Args...)> func = bindHelper(f,o,subt, std::make_index_sequence<sizeof...(Args)>{});
        setter->addCallback(func, o);
        if (o != this)
            o->m_senders.push_back(this);
    }

    template<typename ...Args>
    void connect(const std::string &key,void(*f)(Args...)){
        AbstractSetterCallable *sc = m_setterMap[key];
        if (!sc)
            return;
        Setter<Args...> *setter = dynamic_cast<Setter<Args...> *>(sc);
        if (!setter)
          return;
        std::function<void(Args...)> func(f);
        setter->addCallback(func);
    }

    template <typename F, typename ...Args>
    void connect(const std::string &key, F f){
        AbstractSetterCallable *sc = m_setterMap[key];
        if (!sc)
            return;
        Setter<Args...> *setter = dynamic_cast<Setter<Args...> *>(sc);
        if (!setter)
            return;
        std::function<void(Args...)> func(f);
        setter->addCallback(func);
    }

    void disconnect(AbstractClass *receiver){
        for (auto &pair : m_setterMap){
            pair.second->removeAssociatedCallbacks(dynamic_cast<AbstractClassPrivate*>(receiver));
        }
    }
    void disconnect(const std::string &key, AbstractClass *receiver)
    {
        AbstractSetterCallable *setter = m_setterMap[key];
        setter->removeAssociatedCallbacks(receiver);
    }


private:
    std::vector<AbstractClass*> m_senders;
    AbstractClass *m_this;
    void __delete()
    {
        delete this;
    }


    std::tuple<decltype(std::placeholders::_1),
               decltype(std::placeholders::_2),
               decltype(std::placeholders::_3),
               decltype(std::placeholders::_4)> m_placeholders;


    std::map<std::string,AbstractSetterCallable*> m_setterMap;
    mutable std::map<std::string,AbstractGetterCallable*> m_getterMap;
};


#endif
