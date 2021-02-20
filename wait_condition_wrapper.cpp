#include "wait_condition_wrapper.h"

WaitConditionWrapper::WaitConditionWrapper() {
  impl_ = new CWaitCondition_Impl();
}

WaitConditionWrapper::~WaitConditionWrapper() {
  if (impl_) {
    delete impl_;
  }
}

void WaitConditionWrapper::wait(const MutexWrapper* mutex) {
  impl_->wait(mutex->getImpl());
}

void WaitConditionWrapper::wakeAll() { return impl_->wakeAll(); }
