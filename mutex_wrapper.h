#ifndef __SMARTAUDIOSTUDIO_MUTEXWRAPPER_H__
#define __SMARTAUDIOSTUDIO_MUTEXWRAPPER_H__

#include <QMutex>

class CMutex_Impl: public QMutex
{

};

class MutexWrapper
{
public:
    MutexWrapper();
    ~MutexWrapper();
    void lock();
    void unlock();
    CMutex_Impl* getImpl() const { return impl_; }
private:
    CMutex_Impl* impl_;
};

#endif /* __SMARTAUDIOSTUDIO_MUTEXWRAPPER_H__ */
