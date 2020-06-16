#ifndef __Event_h__
#define __Event_h__

#include "abstract_module.h"
#include "dispatcher.h"
//#include "base_message.h"
//#include "message_types.h"

#include "brain.h"
#include "stdlibs.h"

namespace brain {
class Event : public BaseMessage {
 public:
  Event(messagetypes::EMessageTypes _type) : BaseMessage(_type){};
  PropertyListPtr properties;
  PredictionStatus::Enum status;
  Timestamp timestamp;
};
}  // namespace brain

#endif
