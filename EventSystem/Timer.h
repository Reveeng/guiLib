#ifndef TIMER_H
#define TIMER_H

#include <Event.h>
#include <EventLoop.h>
#include <thread>
#include <condition_variable>

/**
 * @brief Create timer. Run functon that set by setTimerFunction in
 * separated thread. Neet to write callback function threadsafe
 * Not thread safe by default!
 */
template <class T, typename std::enable_if_t<std::is_base_of_v<AbstractEvent,T>, bool> = true>
class Timer
{
public:
    Timer();
    ~Timer();
    Timer(const T&);
    /**
     * @brief start timer with setted time
     * @return true if timer started, false otherwise
     */
    bool start();
    /**
     * @brief start timer with given time
     * @param msec - time in milliseconds
     * @return true if timer started, false otherwise
     */
    bool start(uint32_t msec);
    /**
     * @brief stop timer if it runs
     */
    void stop();

    /**
     * @brief set one time trigger timer
     * @param s - true if need to call callback one time, false - if need to call repeately
     */
    void setSingleShot(bool s);
    /**
     * @brief is timer singleshot
     * @return true - singleshot
     */
    bool isSingleShot() const;

    /**
     * @brief set timer trigger callback function
     * @param cb - callback function
     */
    void setTimerFunction(AbstractEvent *ev);

private:
    void singleShotF();
    void repeatedF();

    bool m_isSingleShot;
    uint32_t m_time;
    std::function<void()>  m_callback;

    std::thread m_timerThread;
    std::condition_variable m_cancelCv;
    std::mutex m_mutex;
};

#endif // TIMER_H
