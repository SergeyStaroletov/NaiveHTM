#ifndef __TIMEPROPERTY_H
#define __TIMEPROPERTY_H

#include "brain.h"
#include "stdlibs.h"

namespace brain {
class TimeProperty : public IProperty {
 private:
  Timestamp offset_;
  Timestamp scale_;

 public:
  PropertyID::Enum GetId();
  IPropertyPtr createByOffset(IOffsetPtr offset);
  IOffsetPtr createOffset(IPropertyPtr property);
  float getDelta(IPropertyPtr property);
  void SetData(Timestamp offset, Timestamp scale);
  Timestamp getOffset();
  Timestamp getScale();
};
}  // namespace brain

#endif  // TIMEPROPERTY_H
