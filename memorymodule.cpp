#include "memorymodule.h"
#include <QProcess>

using namespace std;
using namespace brain;

MemoryModule::MemoryModule(IMemoryPtr memory)  // : dispatcher_(NULL)
{
  memory_ = memory;
  count = 0;
}

void MemoryModule::registerDispatcher(Dispatcher* _dispatcher) {
  this->dispatcher_ = _dispatcher;
}

int MemoryModule::processMessage(BaseMessagePtr _msg) {
  printf("MemoryModule received a message\n");

  // add different message types
  count++;
  // printf("%d\n", count);
  switch (_msg->getType()) {
    case messagetypes::FIXED_CAN_EVENT_BEGIN:
      processBeginning(_msg);
      break;
    case messagetypes::FIXED_CAN_EVENT_END:
      processEnding(_msg);
      break;
    case messagetypes::DATA_END:
      cleanupWindows(_msg);
      break;
    case messagetypes::MODULE_DATA:
      // stub
      break;
    case messagetypes::BRAIN_GIVE_ME_THE_GRAPH: {
      printf("generation graph...\n");

      memory_->getVisualization("graph.txt");

      QStringList list;
      list.append("graph.txt");
      list.append("-O");
      list.append("-Tgif");

      QProcess::execute("dot", list);
      QStringList list2;

      list2.append("graph.txt.gif");
      QProcess::execute("s.bat", list2);
    };

    default:
      return -1;
  }
  return 0;
}

void MemoryModule::processBeginning(BaseMessagePtr _msg) {
  // EventPtr msg((reinterpret_cast<Event*> (_msg.get())));
  EventPtr msg = boost::static_pointer_cast<Event>(_msg);
  beginnings_.push_back(msg);
}

void MemoryModule::processEnding(BaseMessagePtr _msg) {
  // EventPtr msg((reinterpret_cast<Event*> (_msg.get())));
  EventPtr msg = boost::static_pointer_cast<Event>(_msg);

  float inf = (float)(1 << 20);
  float closestDelta = inf;
  float curDelta;
  std::list<EventPtr>::iterator closest;
  for (std::list<EventPtr>::iterator it = beginnings_.begin();
       it != beginnings_.end(); it++) {
    curDelta = msg->properties->getDelta((*it)->properties, strategy_);
    if (curDelta < closestDelta) {
      closestDelta = curDelta;
      closest = it;
    }
  }
  if (closestDelta == inf) {
    throw "End not found!";
    return;
  }
  EventPtr closestEvent = (*closest);
  RealNodePtr real(new RealNode(closestEvent, msg));
  NodeGroupProcessorPtr processor =
      strategy_->getNodeGroupProcessor(real->getPropertyList());
  beginnings_.erase(closest);
  processor->processNode(real);
}

void MemoryModule::cleanupWindows(BaseMessagePtr _msg) {
  strategy_->cleanupWindows();
}

void MemoryModule::setStrategy(IStrategyPtr strategy) { strategy_ = strategy; }

IStrategyPtr MemoryModule::getStrategy() { return strategy_; }

void MemoryModule::setMemory(IMemoryPtr memory) { memory_ = memory; }

IMemoryPtr MemoryModule::getMemory() { return memory_; }
