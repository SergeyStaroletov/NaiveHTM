#include "thread_wrapper.h"

CThread_Impl::CThread_Impl(ThreadWrapper* _owner) { owner_ = _owner; }

void CThread_Impl::run() { return owner_->run(); }

// void CThread_Impl::sleep(unsigned long _time)
//{
//    return QThread::sleep(_time);
//}
//
// void CThread_Impl::msleep(unsigned long _time)
//{
//    return QThread::msleep(_time);
//}
//
// void CThread_Impl::usleep(unsigned long _time)
//{
//    return QThread::usleep(_time);
//}

ThreadWrapper::ThreadWrapper() { impl_ = new CThread_Impl(this); }

ThreadWrapper::~ThreadWrapper() {
  if (impl_) {
    delete impl_;
  }
}

void ThreadWrapper::start(Priority _p) {
  return impl_->start((QThread::Priority)_p);
}

void ThreadWrapper::terminate() { return impl_->terminate(); }

void ThreadWrapper::quit() { return impl_->quit(); }

bool ThreadWrapper::wait(unsigned long _time) { return impl_->wait(_time); }

// void ThreadWrapper::sleep(unsigned long _time)
//{
//    return CThread_Impl::sleep(_time);
//}
//
// void ThreadWrapper::msleep(unsigned long _time)
//{
//    return CThread_Impl::msleep(_time);
//}
//
// void ThreadWrapper::usleep(unsigned long _time)
//{
//    return CThread_Impl::usleep(_time);
//}
