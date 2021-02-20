#include "hypothesis.h"

using namespace std;
using namespace brain;

Hypothesis::Hypothesis(IStrategyPtr strategy) { strategy_ = strategy; }

Hypothesis::~Hypothesis() {
  delete nodes_;
  delete links_;
}

void Hypothesis::setNodes(std::vector<NodePtr>* nodes) { nodes_ = nodes; }

vector<NodePtr>* Hypothesis::getNodes() { return nodes_; }

void Hypothesis::setLinks(std::vector<LinkPtr>* links) { links_ = links; }

vector<LinkPtr>* Hypothesis::getLinks() { return links_; }

void Hypothesis::setAmount(int amount) { amount_ = amount; }

RealNodePtr Hypothesis::getTopNode() { return topNode; }

void Hypothesis::setTopNode(RealNodePtr realNode) { topNode = realNode; }

int Hypothesis::getAmount() { return amount_; }

void Hypothesis::setRealNodes(std::vector<RealNodePtr>* realNodes) {
  realNodes_ = realNodes;
}

std::vector<RealNodePtr>* Hypothesis::getRealNodes() { return realNodes_; }

bool Hypothesis::isSame(HypothesisPtr hypothesis) {
  float inf = (float)(1 << 20);
  float minSum = inf;
  if (links_->size() != hypothesis->getLinks()->size()) {
    /*CompareResult result;
    result.delta = inf;
    result.assignation = vector<LinkPtr>();
    return result;*/
    return false;
  }
  set<LinkPtr> usedLinks;
  float deltaSum = 0.0f;
  usedLinks.clear();
  vector<LinkPtr>* enemy = hypothesis->getLinks();
  LinkPtr curLink;
  for (int i = 0; i < links_->size(); i++) {
    float minDelta = inf;
    for (int j = 0; j < enemy->size(); j++) {
      if (usedLinks.find((*enemy)[i]) != usedLinks.end()) continue;
      float delta =
          (*links_)[i]->offsets->getDelta((*enemy)[i]->offsets, strategy_);
      if (delta < minDelta) {
        minDelta = delta;
        curLink = (*enemy)[j];
      }
    }
    if (minDelta < inf) {
      usedLinks.insert(curLink);
      deltaSum += minDelta;
    } else {
      return false;
    }
  }
  if (deltaSum > strategy_->getMaxDelta()) return false;
  return true;
}
