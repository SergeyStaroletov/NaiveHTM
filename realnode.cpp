#include "realnode.h"

using namespace std;
using namespace brain;

RealNode::RealNode() {}

RealNode::RealNode(EventPtr beginning, EventPtr ending) {
  propertyList = beginning->properties;
  TimePropertyPtr tp(new TimeProperty());
  tp->SetData(beginning->timestamp, ending->timestamp - beginning->timestamp);
  propertyList->setProperty(tp);
  node = NodePtr(new Node());
  node->id =
      -((BaseProperty<NodeId, PropertyID::HyperSensorId,
                      BaseDiffType::Add>*)(propertyList
                                               ->getProperty(
                                                   PropertyID::HyperSensorId))
            .get())
           ->getData();
}

void RealNode::fillProperties(RealNodePtr sourceNode, OffsetListPtr offset) {
  PropertyListPtr props = sourceNode->getPropertyList();
  propertyList = props->createByOffset(offset);
}

NodePtr RealNode::getNode() { return node; }

void RealNode::setNode(NodePtr node) { this->node = node; }

void RealNode::setPropertyList(PropertyListPtr list) {
  this->propertyList = list;
}

PropertyListPtr RealNode::getPropertyList() { return this->propertyList; }
