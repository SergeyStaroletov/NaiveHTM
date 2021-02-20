#ifndef __PROPERTYLIST_H
#define __PROPERTYLIST_H

#include "brain.h"
#include "stdlibs.h"

namespace brain {
class PropertyList {
 private:
  std::map<PropertyID::Enum, IPropertyPtr> properties_;

 public:
  PropertyList();
  void setProperty(IPropertyPtr property);
  bool containsProperty(PropertyID::Enum id);
  IPropertyPtr getProperty(PropertyID::Enum id);
  void mergeWith(PropertyListPtr properties);
  void clear();

  PropertyListPtr createByOffset(OffsetListPtr offsets);
  OffsetListPtr createOffset(PropertyListPtr properties);
  float getDelta(PropertyListPtr properties, IStrategyPtr strategy);
};
}  // namespace brain

#endif  // PROPERTYLIST_H
