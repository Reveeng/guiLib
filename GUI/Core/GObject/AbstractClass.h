#ifndef ABSTRACTCLASS_H
#define ABSTRACTCLASS_H


#include <functional>
#include <map>
#include <string>
#include <type_traits>
#include <vector>

#include <iostream>

template <std::size_t I = 0, typename... Tp,
          std::enable_if_t<I == sizeof...(Tp),bool> = true>
inline bool setter(std::tuple<Tp&...> &refs, const std::tuple<Tp...> &vals, bool isSame)
{
    (void)refs;
    (void)vals;
    return isSame;
}

template <std::size_t I = 0, typename... Tp, std::enable_if_t<I < sizeof...(Tp),bool> = true>
inline bool setter(std::tuple<Tp&...> &refs, const std::tuple<Tp...> &vals, bool isSame = true)
{
    auto& ref = std::get<I>(refs);
    auto val = std::get<I>(vals);
    isSame &= ref == val;
    ref = val;
    return setter<I+1, Tp...>(refs,vals, isSame);
}
template<typename Function, typename Tuple, std::size_t ...I>
auto callHelper(Function f, Tuple &t, std::index_sequence<I...>){
    return f(std::get<I>(t)...);
}

template<typename Function, class Owner, typename Tuple, std::size_t ...I>
auto bindHelper(Function f, Owner *o, Tuple &t, std::index_sequence<I...>){
  return std::bind(f,o, std::get<I>(t)...);
}

template <typename... T, std::size_t... I>
auto subtuple(const std::tuple<T...>&t, std::index_sequence<I...>){
  return std::make_tuple(std::get<I>(t)...);
}


class AbstractSetterCallable{
public:
    virtual ~AbstractSetterCallable(){};
};

class AbstractSetterCallback{
public:
    virtual ~AbstractSetterCallback(){}
};

template <typename ...Args>
class Setter : public AbstractSetterCallable{

public:
    Setter():
        AbstractSetterCallable(),
        m_argSize(sizeof...(Args))
    {

    }
    Setter(Args &... refs):
        AbstractSetterCallable(),
        m_argSize(sizeof...(Args)),
        m_objectDataRefs(std::make_tuple(std::ref(refs)...))
    {

    }

    void storeReferences(Args &... refs){
        m_objectDataRefs = std::make_tuple(std::ref(refs)...);
    }

    std::size_t size() const{
        return m_argSize;
    }

    bool invoke(const Args &... val)
    {
        auto vals = std::make_tuple(val...);
        return !setter(m_objectDataRefs, vals);
    }

    void addCallback(std::function<void(Args...)> f){
        m_cbs.push_back(f);
    }
private:
    std::size_t m_argSize;
    std::tuple<Args &...> m_objectDataRefs;
    std::vector<std::function<void(Args...)>> m_cbs;
};

class AbstractClass;

class AbstractSignalCallbackConnector
{
public:
    AbstractSignalCallbackConnector(AbstractClass *sigp):
        m_signalProvider(sigp)
    {

    }
    virtual ~AbstractSignalCallbackConnector(){}

    virtual void removeAssociatedCallbacks(AbstractClass *cp) = 0;

protected:
    AbstractClass *m_signalProvider;
    AbstractSetterCallable *m_setter;
};

template<typename ...Args>
class SignalCallbackConnector : public AbstractSignalCallbackConnector
{
public:
    SignalCallbackConnector(AbstractClass *sigP, Args&... args):
          AbstractSignalCallbackConnector(sigP)
    {
        Setter<Args...> * set = new Setter<Args...>(args...);
        m_setter = dynamic_cast<AbstractSetterCallable*>(set);
    }

    ~SignalCallbackConnector(){
        delete m_setter;
    }

    void invoke(Args ... args)
    {
        Setter<Args...> *set = dynamic_cast<Setter<Args...> *>(m_setter);
        if (!set)
            return;
        bool changed = set->invoke(args...);
        if (changed)
            invokeCallbacks(args...);
    }


    void addCallback(std::function<void(Args...)> f, AbstractClass *cp = nullptr)
    {
        auto &vec = m_callbacksMap[cp];
        vec.push_back(f);
    }

    virtual void removeAssociatedCallbacks(AbstractClass *cp) override final
    {
        if (!cp)
            return;
        m_callbacksMap.erase(cp);
    }

private:
    void invokeCallbacks(Args &... args)
    {
        for (auto &pair : m_callbacksMap){
            for (auto f : pair.second  )
                f(args...);
        }
    }
    std::map<AbstractClass *, std::vector<std::function<void(Args...)>>> m_callbacksMap;
};


class AbstractClass
{
public:
    AbstractClass(){}
    ~AbstractClass()
    {
        for (auto &pair : m_setterMap){
            delete pair.second;
        }
        for (auto sender : m_senders){
            sender->disconnect(this);
        }
    }
    template<class RecObject, typename ...Args>
    static void connect(AbstractClass *sp, const std::string &key, RecObject *cp, void(RecObject::*f)(Args...))
    {
      sp->connect(key,f,cp);
    }


protected:
    template <typename ...Args>
    void createObjectSetter(const std::string &key, Args&... args){
        SignalCallbackConnector<Args...> *connector = new SignalCallbackConnector<Args...>(this,args...);
        m_setterMap[key] = dynamic_cast<AbstractSignalCallbackConnector*>(connector);
    }

    template <typename ...Args>
    void invokeSetter(const std::string &key, const Args&... args){
        AbstractSignalCallbackConnector *sc = m_setterMap[key];
        if (!sc)
            return;
        SignalCallbackConnector<Args...> *setter = dynamic_cast<SignalCallbackConnector<Args...> *>(sc);
        setter->invoke(args...);
    }

    template<class RecObject, typename ...Args,
             std::enable_if_t<std::is_base_of_v<AbstractClass,RecObject>,bool> = true>
    void connect(const std::string &key, void(RecObject::*f)(Args...),RecObject *o){
        AbstractSignalCallbackConnector *sc = m_setterMap[key];
        if (!sc)
          return;
        SignalCallbackConnector<Args...> *setter = dynamic_cast<SignalCallbackConnector<Args...> *>(sc);
        auto subt = subtuple(m_placeholders,std::make_index_sequence<sizeof...(Args)>{});
        std::function<void(Args...)> func = bindHelper(f,o,subt, std::make_index_sequence<sizeof...(Args)>{});
        setter->addCallback(func, o);
        if (o != this)
            o->m_senders.push_back(this);
    }

    template<typename ...Args>
    void connect(const std::string &key,void(*f)(Args...)){
        AbstractSignalCallbackConnector *sc = m_setterMap[key];
        if (!sc)
            return;
        SignalCallbackConnector<Args...> *setter = dynamic_cast<SignalCallbackConnector<Args...> *>(sc);
        if (!setter)
          return;
        std::function<void(Args...)> func(f);
        setter->addCallback(func);
    }

    void disconnect(AbstractClass *receiver){
        for (auto &pair : m_setterMap){
            pair.second->removeAssociatedCallbacks(receiver);
        }
    }


private:
    std::vector<AbstractClass*> m_senders;


    std::tuple<decltype(std::placeholders::_1),
               decltype(std::placeholders::_2),
               decltype(std::placeholders::_3),
               decltype(std::placeholders::_4)> m_placeholders;


    std::map<std::string, AbstractSignalCallbackConnector*> m_setterMap;
};

#endif // ABSTRACTCLASS_H
