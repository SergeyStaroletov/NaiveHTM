#include "propertylist.h"

using namespace std;
using namespace brain;

PropertyList::PropertyList() {}

void PropertyList::clear() { properties_.clear(); }

bool PropertyList::containsProperty(PropertyID::Enum id) {
  return (properties_.find(id) != properties_.end());
}

IPropertyPtr PropertyList::getProperty(PropertyID::Enum id) {
  if (!containsProperty(id)) {
    throw "Property list doesn't contain some id";
  }
  return properties_[id];
}

void PropertyList::mergeWith(PropertyListPtr properties) {
  for (std::map<PropertyID::Enum, IPropertyPtr>::iterator it =
           properties->properties_.begin();
       it != properties->properties_.end(); it++) {
    if (!containsProperty(it->first)) {
      setProperty(it->second);
    }
  }
}

void PropertyList::setProperty(IPropertyPtr property) {
  properties_[property->GetId()] = property;
}

PropertyListPtr PropertyList::createByOffset(OffsetListPtr offsets) {
  PropertyListPtr result(new PropertyList());
  for (map<PropertyID::Enum, IPropertyPtr>::iterator it = properties_.begin();
       it != properties_.end(); it++) {
    IOffsetPtr offset = offsets->getOffset(it->first);
    IPropertyPtr prop = it->second;
    IPropertyPtr newProp = prop->createByOffset(offset);
    result->setProperty(newProp);
  }
  return result;
}

OffsetListPtr PropertyList::createOffset(PropertyListPtr props) {
  OffsetListPtr result(new OffsetList());
  for (map<PropertyID::Enum, IPropertyPtr>::iterator it = properties_.begin();
       it != properties_.end(); it++) {
    IPropertyPtr prop = it->second;
    IOffsetPtr offset(prop->createOffset(props->getProperty(it->first)));
    result->setOffset(offset);
  }
  return result;
}

float PropertyList::getDelta(PropertyListPtr props, IStrategyPtr strategy) {
  float result = 0.0f;
  for (map<PropertyID::Enum, IPropertyPtr>::iterator it = properties_.begin();
       it != properties_.end(); it++) {
    IPropertyPtr prop = it->second;
    float delta = prop->getDelta(props->getProperty(it->first)) *
                  strategy->getWeight(it->first);
    result += delta;
  }
  return result;
}
