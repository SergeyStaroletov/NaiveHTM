#include "mutex_wrapper.h"

MutexWrapper::MutexWrapper() { impl_ = new CMutex_Impl(); }

MutexWrapper::~MutexWrapper() {
  if (impl_) {
    delete impl_;
  }
}

void MutexWrapper::lock() { return impl_->lock(); }

void MutexWrapper::unlock() { return impl_->unlock(); }
