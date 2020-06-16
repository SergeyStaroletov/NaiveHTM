#ifndef __DISPATCHER_H__
#define __DISPATCHER_H__

#include <map>
#include "base_message.h"

// class BaseMessage;
class IMessageHandler;

class Dispatcher {
 public:
  Dispatcher();
  ~Dispatcher();
  void registerMessageHandler(const unsigned int _msgType,
                              IMessageHandler* _msgHandler);
  bool unregisterMessageHandler(const unsigned int _msgType,
                                const IMessageHandler* _msgHandler);
  bool unregisterMessageHandler(const IMessageHandler* _msgHandler);
  bool dispatchMessage(const BaseMessagePtr _baseMsg);

 private:
  typedef std::multimap<unsigned int, IMessageHandler*> HandlersTable;
  HandlersTable handlersMap;

  bool removeHandlers(HandlersTable::iterator _begin,
                      HandlersTable::iterator _end,
                      const IMessageHandler* _handler);
};

#endif
