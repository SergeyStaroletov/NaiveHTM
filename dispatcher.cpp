#include "dispatcher.h"
#include "base_message.h"
#include "i_message_handler.h"

Dispatcher::Dispatcher() {}

Dispatcher::~Dispatcher() { handlersMap.clear(); }

void Dispatcher::registerMessageHandler(const unsigned int _msgType,
                                        IMessageHandler* _msgHandler) {
  handlersMap.insert(std::make_pair(_msgType, _msgHandler));
}

bool Dispatcher::unregisterMessageHandler(const unsigned int _msgType,
                                          const IMessageHandler* _msgHandler) {
  return removeHandlers(handlersMap.lower_bound(_msgType),
                        handlersMap.upper_bound(_msgType), _msgHandler);
}

bool Dispatcher::unregisterMessageHandler(const IMessageHandler* _msgHandler) {
  return removeHandlers(handlersMap.begin(), handlersMap.end(), _msgHandler);
}

bool Dispatcher::dispatchMessage(const BaseMessagePtr _baseMsg) {
  HandlersTable::const_iterator current =
      handlersMap.lower_bound(_baseMsg->getType());
  HandlersTable::const_iterator end =
      handlersMap.upper_bound(_baseMsg->getType());
  bool result = false;
  while (end != current) {
    if (current->second != NULL) {
      current->second->passMessage(_baseMsg);
      ++current;
      result = true;
    }
  }

  return result;
}

bool Dispatcher::removeHandlers(HandlersTable::iterator _begin,
                                HandlersTable::iterator _end,
                                const IMessageHandler* _handler) {
  bool result = false;
  while (_end != _begin) {
    if (_begin->second == _handler) {
      HandlersTable::iterator deleting = _begin++;
      handlersMap.erase(deleting);
      result = true;
      continue;
    }
    ++_begin;
  }
  return result;
}
