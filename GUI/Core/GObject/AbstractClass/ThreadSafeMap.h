#ifndef THREADSAFEMAP_H
#define THREADSAFEMAP_H
#include <string>
#include <map>
#include <mutex>

template <typename T>
class ThreadSafeMap : public std::map<std::string, T>
{
public:
    void lock(){
        m_dataMutex.lock();
    }

    void unlock(){
        m_dataMutex.unlock();
    }

    void emplace(const std::string &k, T &&o){
        m_dataMutex.lock();
        std::map<std::string, T>::emplace(k,o);
        m_dataMutex.unlock();
    }

    T &get(const std::string &k){
        std::lock_guard<std::mutex> g(m_dataMutex);
        return this->operator[](k);
    }

private:
    std::mutex m_dataMutex;
};


#endif // THREADSAFEMAP_H
