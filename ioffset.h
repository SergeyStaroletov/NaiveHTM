#ifndef __IOFFSET_H
#define __IOFFSET_H

#include "brain.h"
#include "stdlibs.h"

namespace brain {
class IOffset {
 public:
  virtual PropertyID::Enum getPropertyId() = 0;
  virtual IOffsetPtr getInverted() = 0;
  virtual float getDelta(IOffsetPtr offset) = 0;
  virtual void makeAverage(IOffsetPtr offset, float weight) = 0;
  virtual void outputToStream(std::ostream &out) = 0;
};
}  // namespace brain
#endif
