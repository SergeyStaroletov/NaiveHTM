#ifndef __HYPOTHESIS_H
#define __HYPOTHESIS_H

#include "brain.h"
#include "stdlibs.h"

namespace brain {
class Hypothesis {
 private:
  std::vector<NodePtr>* nodes_;
  std::vector<LinkPtr>* links_;
  std::vector<RealNodePtr>* realNodes_;
  RealNodePtr topNode;
  int amount_;
  IStrategyPtr strategy_;

 public:
  Hypothesis(IStrategyPtr strategy);
  ~Hypothesis();

  std::vector<NodePtr>* getNodes();
  void setNodes(std::vector<NodePtr>* nodes);

  std::vector<LinkPtr>* getLinks();
  void setLinks(std::vector<LinkPtr>* links);

  std::vector<RealNodePtr>* getRealNodes();
  void setRealNodes(std::vector<RealNodePtr>* realNodes);

  RealNodePtr getTopNode();
  void setTopNode(RealNodePtr realNode);

  int getAmount();
  void setAmount(int amount);

  bool isSame(HypothesisPtr hypothesis);
};
}  // namespace brain

#endif
