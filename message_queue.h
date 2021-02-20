#ifndef __SMARTAUDIOSTUDIO_MESSAGEQUEUE_H__
#define __SMARTAUDIOSTUDIO_MESSAGEQUEUE_H__

#include <list>
#include <QtCore/QMutex>

#include "base_message.h"

class MessageQueue {
public:
    MessageQueue();
    ~MessageQueue();
    void putMessage(const BaseMessagePtr _msg);
    bool popMessage(BaseMessagePtr& _msg);
    int getSize();

private:
    std::list<BaseMessagePtr> messagesQueue;
    QMutex mutex;
};

#endif /* __SMARTAUDIOSTUDIO_MESSAGEQUEUE_H__ */
