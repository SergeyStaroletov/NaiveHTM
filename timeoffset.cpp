#include "timeoffset.h"

using namespace std;
using namespace brain;

TimeOffset::TimeOffset() {}

PropertyID::Enum TimeOffset::getPropertyId() { return PropertyID::Time; }

IOffsetPtr TimeOffset::getInverted() {
  TimeOffset* t = new TimeOffset();
  t->SetData(-offset_, 1.0f / scale_);
  return IOffsetPtr(t);
}

void TimeOffset::SetData(float offset, float scale) {
  this->offset_ = offset;
  this->scale_ = scale;
}

float TimeOffset::getOffset() { return offset_; }

float TimeOffset::getScale() { return scale_; }

float TimeOffset::getDelta(IOffsetPtr property) {
  TimeOffset* t = (TimeOffset*)property.get();

  // Timestamp a = Util//Utils::abs(offset - t->getOffset()) /
  Timestamp a = max(offset_, t->offset_);
  Timestamp b = min(offset_ + scale_, t->getOffset() + t->getScale());
  if (a >= b) return 1.0f;
  return 1.0f - (float)(b - a) / (0.5f * (t->getScale() + scale_));
}

void TimeOffset::makeAverage(IOffsetPtr offset, float weight) {
  TimeOffset* t = (TimeOffset*)offset.get();
  offset_ = ((offset_ + weight * t->getOffset()) / (1.0f + weight));
  scale_ = ((scale_ + weight * t->getScale()) / (1.0f + weight));
}

void TimeOffset::outputToStream(std::ostream& out) {
  out << offset_ << " + " << scale_;
}
