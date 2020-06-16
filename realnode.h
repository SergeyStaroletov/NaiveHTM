#ifndef __REALNODE_H
#define __REALNODE_H

#include "brain.h"
#include "stdlibs.h"

namespace brain {
class RealNode {
 private:
  NodePtr node;
  PropertyListPtr propertyList;

 public:
  RealNode();
  RealNode(EventPtr beginning, EventPtr ending);
  NodePtr getNode();
  void setNode(NodePtr node);
  PropertyListPtr getPropertyList();
  void setPropertyList(PropertyListPtr list);
  void fillProperties(RealNodePtr sourceNode, OffsetListPtr offset);
};
}  // namespace brain
#endif  // REALNODE_H
