#include "mystrategy.h"

using namespace std;
using namespace brain;

#define dsec 100000LL;

MyStrategy::MyStrategy()
{
  // memoryModule_ = memoryModule;
  // storage_ = storage;

  // create parents map (all processors)
  /*
    casual instruments = 1
    drums = 2
    rhythm signals = 3
    */
}

/*
Time in microseconds, w ~ 1.0f / 1000000.0f
Tone in piano key number - halftones, w ~ 0.5f
Velocity - not important, w ~ 0.0f
HyperSensorId - not comparable, getMaxDelta = 0.0f, w ~ inf
InstrumentId - comparable, w ~ 1.0f
*/

std::vector<NodeGroupProcessorPtr> MyStrategy::getParents(
    NodeGroupProcessorPtr node) {
  if (parents.find(node) == parents.end()) {
    if (node->getLevel() > 6) return vector<NodeGroupProcessorPtr>();
    NodeGroupProcessorPtr proc(new NodeGroupProcessor(
        memoryModule_, storage_, IStrategyPtr(this), node->getLevel() + 1));
    parents[node].push_back(proc);
  }
  return parents[node];
}

void MyStrategy::cleanupWindows() {
  for (std::map<HyperSensorId, NodeGroupProcessorPtr>::iterator it =
           zeroLevel.begin();
       it != zeroLevel.end(); it++) {
    it->second->cleanupWindows();
  }
  for (std::map<NodeGroupProcessorPtr,
                std::vector<NodeGroupProcessorPtr> >::iterator it =
           parents.begin();
       it != parents.end(); it++) {
    it->first->cleanupWindows();
    for (std::vector<NodeGroupProcessorPtr>::iterator iter = it->second.begin();
         iter != it->second.end(); iter++) {
      (*iter)->cleanupWindows();
    }
  }
}

int MyStrategy::getMinimalOccurrencesNumber(NodeGroupProcessorPtr nodeGroup) {
  return 2;
}

float MyStrategy::getMaxDelta(PropertyID::Enum propertyID) { return 50.0f; }
float MyStrategy::getMaxDelta(NodePtr node) {
  return 5.0f;  // 0.5f
}

float MyStrategy::getMaxDelta() { return 1000.0f; }

long long MyStrategy::getSmallWindowSize(NodeGroupProcessorPtr nodeGroup) {
  return (1 << nodeGroup->getLevel()) * 4 * dsec;
}

long long MyStrategy::getBigWindowSize(NodeGroupProcessorPtr nodeGroup) {
  return (1 << nodeGroup->getLevel()) * 100 * dsec;
}

int MyStrategy::getSmallWindowElementsNumber(
    NodeGroupProcessorPtr nodeGroup) {
  return 5;
}

float MyStrategy::getWeight(PropertyID::Enum propertyID) {
  switch (propertyID) {
    case PropertyID::Tone:
      return 1.0f;
    case PropertyID::InstrumentID:
      return 10.0f;
    case PropertyID::Time:
      return 3.0f;
  }
  return 0.0f;
}

void MyStrategy::setMemory(MemoryModulePtr memoryModule, IMemoryPtr storage) {
  memoryModule_ = memoryModule;
  storage_ = storage;
}

NodeGroupProcessorPtr MyStrategy::getNodeGroupProcessor(
    PropertyListPtr properties) {
  if (!properties->containsProperty(PropertyID::HyperSensorId)) {
    throw "Property list doesn't contain HyperSensorId";
  }
  IPropertyPtr hs = properties->getProperty(PropertyID::HyperSensorId);
  HyperSensorIdProperty* hsptr = (HyperSensorIdProperty*)hs.get();
  HyperSensorId id = (HyperSensorId)hsptr->getData();
  if (zeroLevel.find(id) == zeroLevel.end()) {
    NodeGroupProcessorPtr nodeProc(
        new NodeGroupProcessor(memoryModule_, storage_, IStrategyPtr(this), 0));
    zeroLevel[id] = nodeProc;
  }
  return zeroLevel[id];
}
