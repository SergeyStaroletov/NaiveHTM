#include "nodegroupprocessor.h"

using namespace std;
using namespace brain;

NodeGroupProcessor::NodeGroupProcessor(MemoryModulePtr memoryModule,
                                       IMemoryPtr storage,
                                       IStrategyPtr strategy, int level) {
  memoryModule_ = memoryModule;
  storage_ = storage;
  level_ = level;
  this->strategy = strategy;
  smallWindow = std::list<RealNodePtr>(0);
  me = NodeGroupProcessorPtr(this);
}

void NodeGroupProcessor::processNode(RealNodePtr node) {
  smallWindow.push_back(node);
  cleanupSmallWindow(false);
  cleanupBigWindow(false);
  generateHypotheses();
}

void NodeGroupProcessor::cleanupSmallWindow(bool forced) {
  int k = smallWindow.size();
  if (k == 0) return;
  while (smallWindow.size() > strategy->getSmallWindowElementsNumber(me)) {
    smallWindow.erase(smallWindow.begin());
  }
  PropertyListPtr props = smallWindow.back()->getPropertyList();
  IPropertyPtr pr = props->getProperty(PropertyID::Time);
  TimeProperty* to = (TimeProperty*)pr.get();
  while (smallWindow.size() > 0) {
    PropertyListPtr props2 = (smallWindow.front())->getPropertyList();
    IPropertyPtr pr2 = props2->getProperty(PropertyID::Time);
    TimeProperty* to2 = (TimeProperty*)pr2.get();

    Timestamp delta =
        to->getScale() + to->getOffset() - to2->getScale() - to2->getOffset();
    if (delta > strategy->getSmallWindowSize(me))
      smallWindow.erase(smallWindow.begin());
    else
      break;
  }
}

void NodeGroupProcessor::cleanupBigWindow(bool forced) {
  if (bigWindow.size() == 0) return;
  PropertyListPtr props = (smallWindow.back())->getPropertyList();
  IPropertyPtr pr = props->getProperty(PropertyID::Time);
  TimeProperty* to = (TimeProperty*)pr.get();

  if (forced) {
    to = new TimeProperty();
    to->SetData((Timestamp)(1LL << 60LL), 1);
  }

  while (bigWindow.size() > 0) {
    PropertyListPtr props2 =
        (bigWindow.front())->getTopNode()->getPropertyList();
    IPropertyPtr pr2 = props2->getProperty(PropertyID::Time);
    TimeProperty* to2 = (TimeProperty*)pr2.get();

    Timestamp delta =
        to->getScale() + to->getOffset() - to2->getScale() - to2->getOffset();
    if (delta > strategy->getBigWindowSize(me)) {
      if ((bigWindow.front())->getAmount() >=
          strategy->getMinimalOccurrencesNumber(me)) {
        NodePtr node = sendToMemory((bigWindow.front()));
        HypothesisPtr h = (bigWindow.front());
        h->getTopNode()->setNode(node);
        sendToTop(h);
      }
      bigWindow.erase(bigWindow.begin());
    } else
      break;
  }
  if (forced) {
    delete to;
  }
}

void NodeGroupProcessor::cleanupWindows() {
  cleanupSmallWindow(true);
  cleanupBigWindow(true);
}

NodePtr NodeGroupProcessor::sendToMemory(HypothesisPtr hypothesis) {
  IMemoryPtr memory = memoryModule_->getMemory();
  NodePtr node =
      memory->remember(hypothesis->getNodes(), hypothesis->getLinks(),
                       hypothesis->getAmount(), me);
  return node;
}

void NodeGroupProcessor::sendToTop(HypothesisPtr hypothesis) {
  vector<NodeGroupProcessorPtr> parents = strategy->getParents(me);

  for (int i = 0; i < parents.size(); i++) {
    parents[i]->processNode(hypothesis->getTopNode());
  }
}

HypothesisPtr NodeGroupProcessor::createHypothesis(
    vector<RealNodePtr>* realNodes) {
  vector<NodePtr>* nodes = new vector<NodePtr>(realNodes->size());
  vector<LinkPtr>* links = new vector<LinkPtr>(realNodes->size());

  reverse(realNodes->begin(), realNodes->end());
  int n = realNodes->size();

  vector<RealNodePtr>* realNodes_ = new vector<RealNodePtr>(realNodes->size());
  for (int i = 0; i < n; i++) realNodes_->push_back((*realNodes)[i]);

  for (int i = 0; i < n; i++) {
    (*nodes)[i] = (*realNodes)[i]->getNode();
  }

  PropertyListPtr topPropList(new PropertyList());
  for (int i = 0; i < n; i++) {
    topPropList->mergeWith((*realNodes)[i]->getPropertyList());
  }

  for (int i = 0; i < n; i++) {
    RealNodePtr current = (*realNodes)[i];
    OffsetListPtr offsetsList =
        current->getPropertyList()->createOffset(topPropList);
    (*links)[i] = LinkPtr(new Link());
    // PropertyListPtr properties(new PropertyList());
    // properties->
    (*links)[i]->offsets = offsetsList;
    (*links)[i]->amount = 1;
  }
  HypothesisPtr result(new Hypothesis(strategy));
  result->setNodes(nodes);
  result->setLinks(links);
  result->setAmount(1);
  result->setRealNodes(realNodes_);

  RealNodePtr topNode(new RealNode());
  topNode->setPropertyList(topPropList);

  result->setTopNode(topNode);

  return result;
}

void NodeGroupProcessor::generateHypotheses() {
  int number = smallWindow.size();
  int pow = 1 << number;

  for (int k = 3; k < pow; k += 2) {
    int temp = k;
    vector<RealNodePtr> realNodes;
    for (std::list<RealNodePtr>::iterator it = smallWindow.begin();
         it != smallWindow.end(); it++) {
      if (temp % 2 == 1) {
        realNodes.push_back(*it);
      }
      temp /= 2;
    }
    bool was = false;

    HypothesisPtr h = createHypothesis(&realNodes);
    for (list<HypothesisPtr>::iterator it = bigWindow.begin();
         it != bigWindow.end() && !was; it++) {
      if (h->isSame(*it)) {
        ((*it)->setAmount((*it)->getAmount() + 1));

        was = true;
      }
    }
    if (!was) bigWindow.push_back(h);
  }
}

void NodeGroupProcessor::setLevel(int level) { level_ = level; }

int NodeGroupProcessor::getLevel() { return level_; }
