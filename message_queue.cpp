#include "message_queue.h"

MessageQueue::MessageQueue() {
  // TODO:
  //
}

MessageQueue::~MessageQueue() { messagesQueue.clear(); }

void MessageQueue::putMessage(const BaseMessagePtr _msg) {
  mutex.lock();
  messagesQueue.push_back((BaseMessagePtr)_msg);
  mutex.unlock();
}

bool MessageQueue::popMessage(BaseMessagePtr& _msg) {
  mutex.lock();
  _msg = messagesQueue.front();
  messagesQueue.pop_front();
  mutex.unlock();
  return true;
}

int MessageQueue::getSize() { return messagesQueue.size(); }
