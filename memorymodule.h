#ifndef __MEMORYMODULE_H
#define __MEMORYMODULE_H

#include "abstract_module.h"
#include "base_message.h"
#include "dispatcher.h"

//#include "messages/message_types.h"
#include "brain.h"
#include "stdlibs.h"

namespace brain {
class MemoryModule : public AbstractModule  //////
{
 private:
  IStrategyPtr strategy_;
  IMemoryPtr memory_;
  std::list<EventPtr> beginnings_;
  int count;
  //
  Dispatcher* dispatcher_;
  //
  int processConcreteMessage(BaseMessagePtr _msg);

 public:
  MemoryModule(IMemoryPtr memory);
  int processMessage(BaseMessagePtr _msg);
  //
  void registerDispatcher(Dispatcher* _dispatcher);
  //
  IStrategyPtr getStrategy();
  void setStrategy(IStrategyPtr strategy);

  IMemoryPtr getMemory();
  void setMemory(IMemoryPtr memory);

  void processBeginning(BaseMessagePtr _msg);
  void processEnding(BaseMessagePtr _msg);
  void cleanupWindows(BaseMessagePtr _msg);
};
}  // namespace brain
#endif
