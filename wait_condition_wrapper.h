#ifndef ___WAITCONDITIONWRAPPER_H__
#define ___WAITCONDITIONWRAPPER_H__

#include <QMutex>
#include <QWaitCondition>

#include "mutex_wrapper.h"

class CWaitCondition_Impl : public QWaitCondition {};

class WaitConditionWrapper {
 public:
  WaitConditionWrapper();
  ~WaitConditionWrapper();
  void wait(const MutexWrapper*);
  void wakeAll();

 private:
  CWaitCondition_Impl* impl_;
};

#endif /* __SMARTAUDIOSTUDIO_WAITCONDITIONWRAPPER_H__ */
