#include <stdio.h>

#include "abstract_module.h"
#include "message_types.h"

// void SleepingThread::sleep(unsigned long _time)
//{
//    return ThreadWrapper::sleep(_time);
//}
//
// void SleepingThread::msleep(unsigned long _time)
//{
//    return ThreadWrapper::msleep(_time);
//}
//
// void SleepingThread::usleep(unsigned long _time)
//{
//    return ThreadWrapper::usleep(_time);
//}

AbstractModule::AbstractModule(unsigned int depth)
    : max_msgqueue_depth_(depth), stop_flag_(false) {
  printf("Abstract module c'tor\n");
}

AbstractModule::~AbstractModule() {}

void AbstractModule::setMaxQueueDepth(unsigned int depth) {
  max_msgqueue_depth_ = depth;
}

void AbstractModule::passMessage(const BaseMessagePtr _msg) {
  queue_mutex_.lock();
  while (msgQueue.getSize() == max_msgqueue_depth_) {
    // printf("Queue full. Waitng...\n");
    queue_not_full_.wait(&queue_mutex_);
    // printf("Queue have an empty space.\n");
  }
  msgQueue.putMessage(_msg);
  queue_mutex_.unlock();
  queue_not_empty_.wakeAll();
}

void AbstractModule::run() {
  while (!stop_flag_) {
    queue_mutex_.lock();
    while (msgQueue.getSize() == 0) {
      //   printf("Queue empty. Waitng...\n");
      queue_not_empty_.wait(&queue_mutex_);
      //  printf("Queue have at least one element.\n");
    }

    BaseMessagePtr msg;
    msgQueue.popMessage(msg);

    queue_mutex_.unlock();
    queue_not_full_.wakeAll();

    if (msg != NULL) {
      if (msg->getType() == messagetypes::EXIT) {
        stop();
      } else {
        processMessage(msg);
      }
    }
  }
}

void AbstractModule::stop() { stop_flag_ = true; }
