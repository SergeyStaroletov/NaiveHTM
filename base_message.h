#ifndef __SMARTAUDIOSTUDIO_BASEMESSAGE_H__
#define __SMARTAUDIOSTUDIO_BASEMESSAGE_H__

#include "message_types.h"
#include <boost/smart_ptr.hpp>


using namespace messagetypes;

class BaseMessage
{
public:
    BaseMessage(EMessageTypes _type) : type_(_type) {};
    virtual ~BaseMessage() {};
    EMessageTypes getType() const { return type_; };
    void setMessageType(EMessageTypes _type) { type_ = _type;};
protected:
    EMessageTypes type_;
};


typedef boost::shared_ptr<BaseMessage> BaseMessagePtr;



#endif /* __SMARTAUDIOSTUDIO_BASEMESSAGE_H__ */
