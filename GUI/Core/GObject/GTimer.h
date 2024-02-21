#ifndef GTIMER_H
#define GTIMER_H

#include <thread>
#include <condition_variable>
#include <AbstractClass.h>


class GTimer : public AbstractClass{
public:
    GTimer(uint32_t timerId = 0);
    ~GTimer();

    bool start();
    bool start(uint32_t msec);
    void stop();

    void setSingleShot(bool sh);
    bool isSingleShot() const;

    void setDetached(bool d);
    bool isDetached() const;

    uint32_t id() const;

protected:
    void singleShotF();
    void repeatedF();

private:
    void __start();
    bool m_isSingleShot;
    bool m_isDetached;
    uint32_t m_time;

    std::condition_variable m_cancelCv;
    std::mutex m_mutex;
    uint32_t m_id;
};

#endif // GTIMER_H
