#ifndef __OFFSETLIST_H
#define __OFFSETLIST_H

#include "brain.h"
#include "stdlibs.h"

namespace brain {
class OffsetList {
 private:
  std::map<PropertyID::Enum, IOffsetPtr> offsets_;

 public:
  OffsetList();
  IOffsetPtr getOffset(PropertyID::Enum propertyID);
  void setOffset(IOffsetPtr offset);
  OffsetListPtr getInverted();
  float getDelta(OffsetListPtr offsets, IStrategyPtr strategy);
  void makeAverage(OffsetListPtr offsets, float weight);
  void outputToStream(std::ostream& out);
};
}  // namespace brain

#endif
