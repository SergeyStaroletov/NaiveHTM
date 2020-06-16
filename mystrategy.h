#ifndef __MYSTRATEGY_H
#define __MYSTRATEGY_H

#include "brain.h"
#include "stdlibs.h"

namespace brain {
class MyStrategy : public IStrategy {
 private:
  std::map<NodeGroupProcessorPtr, std::vector<NodeGroupProcessorPtr> > parents;
  std::map<HyperSensorId, NodeGroupProcessorPtr> zeroLevel;
  MemoryModulePtr memoryModule_;
  IMemoryPtr storage_;

 public:
  MyStrategy();  //(MemoryModulePtr memoryModule, IMemoryPtr storage);
  void setMemory(MemoryModulePtr memoryModule, IMemoryPtr storage);
  std::vector<NodeGroupProcessorPtr> getParents(NodeGroupProcessorPtr node);
  void cleanupWindows();
  int getMinimalOccurrencesNumber(NodeGroupProcessorPtr nodeGroup);
  float getMaxDelta(PropertyID::Enum propertyID);
  float getMaxDelta(NodePtr node);
  long long getSmallWindowSize(NodeGroupProcessorPtr nodeGroup);
  long long getBigWindowSize(NodeGroupProcessorPtr nodeGroup);
  int getSmallWindowElementsNumber(NodeGroupProcessorPtr nodeGroup);
  float getWeight(PropertyID::Enum propertyID);
  float getMaxDelta();
  NodeGroupProcessorPtr getNodeGroupProcessor(PropertyListPtr properties);
};
}  // namespace brain

#endif
