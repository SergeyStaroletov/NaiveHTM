#include "timeproperty.h"

using namespace std;
using namespace brain;

PropertyID::Enum TimeProperty::GetId() { return PropertyID::Time; }

IOffsetPtr TimeProperty::createOffset(IPropertyPtr property) {
  TimeProperty* t = (TimeProperty*)property.get();
  TimeOffset* res = new TimeOffset();
  if (scale_ == 0) scale_ = 1;
  res->SetData((float)(t->getOffset() - offset_) / (float)scale_,
               (float)t->getScale() / (float)scale_);
  return IOffsetPtr(res);
}

float TimeProperty::getDelta(IPropertyPtr property) {
  TimeProperty* t = (TimeProperty*)property.get();

  // Timestamp a = Util//Utils::abs(offset - t->getOffset()) /
  Timestamp a = max(offset_, t->offset_);
  Timestamp b = min(offset_ + scale_, t->getOffset() + t->getScale());
  if (a >= b) return 1.0f;
  return 1.0f - (float)(b - a) / (0.5f * (t->getScale() + scale_));
}

IPropertyPtr TimeProperty::createByOffset(IOffsetPtr offsetParam) {
  TimeOffset* t = (TimeOffset*)offsetParam.get();
  TimeProperty* res = new TimeProperty();
  res->SetData((Timestamp)(t->getOffset() * scale_) + offset_,
               (Timestamp)(t->getScale() * scale_));
  return IPropertyPtr(res);
}

void TimeProperty::SetData(Timestamp offset, Timestamp scale) {
  this->offset_ = offset;
  this->scale_ = scale;
}

Timestamp TimeProperty::getOffset() { return offset_; }

Timestamp TimeProperty::getScale() { return scale_; }
