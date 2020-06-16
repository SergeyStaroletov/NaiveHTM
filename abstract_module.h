#ifndef __ABSTRACTM_H__
#define __ABSTRACTM_H__

#include "i_message_handler.h"
#include "message_queue.h"
#include "mutex_wrapper.h"
#include "thread_wrapper.h"
#include "wait_condition_wrapper.h"

// class SleepingThread : public ThreadWrapper
//{
// public:
//    static void sleep(unsigned long _time);
//    static void msleep(unsigned long _time);
//    static void usleep(unsigned long _time);
//    virtual ~SleepingThread();
//};

class BaseMessage;

enum { DEFAULT_MAX_QUEUE_DEPTH = 1000000 };

class AbstractModule : public IMessageHandler, public ThreadWrapper {
  WaitConditionWrapper queue_not_full_;
  WaitConditionWrapper queue_not_empty_;
  MutexWrapper queue_mutex_;

  int max_msgqueue_depth_;
  bool stop_flag_;

 public:
  explicit AbstractModule(
      unsigned int max_queue_depth = DEFAULT_MAX_QUEUE_DEPTH);
  virtual ~AbstractModule();
  virtual void passMessage(const BaseMessagePtr _msg);
  virtual void run();
  void stop();
  void setMaxQueueDepth(unsigned int);
  virtual int processMessage(BaseMessagePtr _msg) = 0;

 protected:
  MessageQueue msgQueue;
};

#endif /* __SMARTAUDIOSTUDIO_ABSTRACTRUNNABLE_H__ */
