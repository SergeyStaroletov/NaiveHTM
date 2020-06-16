#ifndef __SMARTAUDIOSTUDIO_THREADWRAPPER_H__
#define __SMARTAUDIOSTUDIO_THREADWRAPPER_H__

#include <QThread>

class ThreadWrapper;

class CThread_Impl: public QThread
{
public:
    CThread_Impl(ThreadWrapper*_owner);
    virtual void run();
//    static void sleep(unsigned long _time);
//    static void msleep(unsigned long _time);
//    static void usleep(unsigned long _time);
private:
    ThreadWrapper* owner_;
};


class ThreadWrapper
{
public:
    enum Priority {
        IdlePriority            = QThread::IdlePriority,
        LowestPriority          = QThread::LowestPriority,
        LowPriority             = QThread::LowPriority,
        NormalPriority          = QThread::NormalPriority,
        HighPriority            = QThread::HighPriority,
        HighestPriority         = QThread::HighestPriority,
        TimeCriticalPriority    = QThread::TimeCriticalPriority,
        InheritPriority         = QThread::InheritPriority
    };

    ThreadWrapper();
    virtual ~ThreadWrapper();
    virtual void run() = 0;

    void start(Priority _p = InheritPriority);
    void terminate();
    void quit();
    bool wait(unsigned long _time = ULONG_MAX);
//    static void sleep(unsigned long _time);
//    static void msleep(unsigned long _time);
//    static void usleep(unsigned long _time);

private:
    CThread_Impl* impl_;
};


#endif /* __SMARTAUDIOSTUDIO_THREADWRAPPER_H__ */
