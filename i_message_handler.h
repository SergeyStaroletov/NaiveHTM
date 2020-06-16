#ifndef __SMARTAUDIOSTUDIO_IMESSAGEHANDLER_H__
#define __SMARTAUDIOSTUDIO_IMESSAGEHANDLER_H__

#include "base_message.h"

class IMessageHandler
{
public:
    virtual void passMessage(const BaseMessagePtr _msg) = 0;
};

#endif /* __SMARTAUDIOSTUDIO_IMESSAGEHANDLER_H__ */
