#ifndef __TIMEOFFSET_H
#define __TIMEOFFSET_H

#include "brain.h"
#include "stdlibs.h"

namespace brain {
class TimeOffset : public IOffset {
 private:
  float offset_;
  float scale_;

 public:
  TimeOffset();
  PropertyID::Enum getPropertyId();
  IOffsetPtr getInverted();
  void SetData(float offset, float scale);
  float getOffset();
  float getScale();
  void makeAverage(IOffsetPtr offset, float weight);
  float getDelta(IOffsetPtr offset);
  void outputToStream(std::ostream &out);
};
}  // namespace brain

#endif  // TIMEOFFSET_H
