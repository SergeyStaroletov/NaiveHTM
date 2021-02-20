#ifndef __ISTRATEGY_H
#define __ISTRATEGY_H

#include "brain.h"
#include "stdlibs.h"

namespace brain {
class IStrategy {
 public:
  virtual std::vector<NodeGroupProcessorPtr> getParents(
      NodeGroupProcessorPtr node) = 0;
  virtual void cleanupWindows() = 0;
  virtual int getMinimalOccurrencesNumber(NodeGroupProcessorPtr nodeGroup) = 0;
  virtual float getMaxDelta(PropertyID::Enum propertyID) = 0;
  virtual float getMaxDelta(NodePtr node) = 0;
  virtual long long getSmallWindowSize(NodeGroupProcessorPtr nodeGroup) = 0;
  virtual long long getBigWindowSize(NodeGroupProcessorPtr nodeGroup) = 0;
  virtual int getSmallWindowElementsNumber(NodeGroupProcessorPtr nodeGroup) = 0;
  virtual float getWeight(PropertyID::Enum propertyID) = 0;
  virtual float getMaxDelta() = 0;
  virtual NodeGroupProcessorPtr getNodeGroupProcessor(
      PropertyListPtr properties) = 0;
  virtual void setMemory(MemoryModulePtr memoryModule, IMemoryPtr storage) = 0;
};
}  // namespace brain
#endif
