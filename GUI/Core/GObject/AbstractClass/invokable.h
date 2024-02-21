#ifndef INVOKABLE_H
#define INVOKABLE_H
#include <functional>
#include <map>
#include <string>

#include <AbstractClassPrivate.h>

template <std::size_t I = 0, typename... Tp,
          std::enable_if_t<I == sizeof...(Tp),bool> = true>
inline bool setter(std::tuple<Tp&...> &refs, const std::tuple<Tp...> &vals, bool isSame = false)
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

template<typename Function, typename Tuple, std::size_t ...I>
auto bindHelper(Function f, Tuple &t, std::index_sequence<I...>)
{
    return std::bind(f, std::get<I>(t)...);
}

template <typename... T, std::size_t... I>
auto subtuple(const std::tuple<T...>&t, std::index_sequence<I...>){
  return std::make_tuple(std::get<I>(t)...);
}

class AbstractSetterCallable{
public:
    virtual ~AbstractSetterCallable(){};
    virtual void removeAssociatedCallbacks(AbstractClassPrivate *) = 0;
};

class AbstractGetterCallable{
public:
    virtual ~AbstractGetterCallable(){};

};

template <typename ...Args>
class Signal
{
public:
    Signal(Args &... refs):
        m_argsSize(sizeof... (Args)),
        m_dataRefs(std::make_tuple(std::ref(refs)...))
    {

    }
    std::size_t size()
    {
        return m_argsSize;
    }

    void addCallback(std::function<void(Args...)> f, AbstractClassPrivate *o =  nullptr)
    {
        auto &cbs = m_callbacks[o];
        cbs.emplace_back(f);
    }

    void invoke()
    {
        invokeCallbacks();
    }

protected:
    std::size_t m_argsSize;
    std::tuple<Args&...> m_dataRefs;
    std::map<AbstractClassPrivate*,std::vector<std::function<void(Args...)>>> m_callbacks;

private:

    void invokeCallbacks()
    {
        for (auto &pair : m_callbacks){
            for (auto &f : pair.second)
                invokeCallback(pair.first, f);
        }
    }
    void invokeCallback(AbstractClassPrivate *o, std::function<void(Args...)> f)
    {
        if (o == nullptr){
            callHelper(f, m_dataRefs,std::make_index_sequence<sizeof...(Args)>{});
            return;
        }
        if (o->isCalledFromObjectThread()){
            callHelper(f, m_dataRefs, std::make_index_sequence<sizeof...(Args)>{});
            return;
        }
        auto fu = bindHelper(f,m_dataRefs, std::make_index_sequence<sizeof...(Args)>{});
        Event<> ev(fu);
        o->eventLoop()->pushEvent(ev);
    }
};

template <typename ...Args>
class Setter : public AbstractSetterCallable , public Signal<Args...>{

public:
    Setter(Args &... refs):
        AbstractSetterCallable(),
        Signal<Args...>(refs...)
    {

    }

    void invoke(const Args &... val)
    {
        auto vals = std::make_tuple(val...);
        if (!setter(this->m_dataRefs, vals)){
            m_cbMutex.lock();
            invokeSignal();
            m_cbMutex.unlock();
        }
    }

    void invokeSignal()
    {
        Signal<Args...>::invoke();
    }

    virtual void removeAssociatedCallbacks(AbstractClassPrivate *cp) override final
    {
        if (!cp)
            return;
        m_cbMutex.lock();
        this->m_callbacks.erase(cp);
        m_cbMutex.unlock();
    }
private:
    std::mutex m_cbMutex;
};

template <typename T>
class Getter : public AbstractGetterCallable{
public:
    Getter(T &ref):
          AbstractGetterCallable(),
          m_ref(ref)
    {

    }

    T invoke()
    {
        return m_ref;
    }
private:
    T& m_ref;
};

#endif // INVOKABLE_H
