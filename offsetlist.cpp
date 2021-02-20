#include "offsetlist.h"

using namespace std;
using namespace brain;

OffsetList::OffsetList() {}

void OffsetList::setOffset(IOffsetPtr offset) {
  offsets_[offset->getPropertyId()] = offset;
}

IOffsetPtr OffsetList::getOffset(PropertyID::Enum propertyID) {
  return offsets_[propertyID];
}

float OffsetList::getDelta(OffsetListPtr offsetList, IStrategyPtr strategy) {
  float result = 0.0f;
  float inf = (float)(1 << 20);
  for (map<PropertyID::Enum, IOffsetPtr>::iterator it = offsets_.begin();
       it != offsets_.end(); it++) {
    IOffsetPtr prop = it->second;
    float delta = prop->getDelta(offsetList->getOffset(it->first)) *
                  strategy->getWeight(it->first);
    if (delta >
        strategy->getMaxDelta(it->first) * strategy->getWeight(it->first))
      return inf;
    result += delta;
  }
  return result;
}

OffsetListPtr OffsetList::getInverted() {
  OffsetListPtr result(new OffsetList());
  for (map<PropertyID::Enum, IOffsetPtr>::iterator it = offsets_.begin();
       it != offsets_.end(); it++) {
    result->setOffset(it->second->getInverted());
  }
  return result;
}

void OffsetList::makeAverage(OffsetListPtr offsets, float weight) {
  for (map<PropertyID::Enum, IOffsetPtr>::iterator it = offsets_.begin();
       it != offsets_.end(); it++) {
    it->second->makeAverage(offsets->getOffset(it->first), weight);
  }
}

void OffsetList::outputToStream(std::ostream &out) {
  for (map<PropertyID::Enum, IOffsetPtr>::iterator it = offsets_.begin();
       it != offsets_.end(); it++) {
    switch (it->first) {
      case PropertyID::Tone:
        out << "Tone: ";
        break;
      case PropertyID::Time:
        out << "Time: ";
        break;
      case PropertyID::HyperSensorId:
        out << "HS: ";
        break;
      case PropertyID::InstrumentID:
        out << "Instr: ";
        break;
      case PropertyID::DrumsID:
        out << "Drums: ";
        break;
    }
    it->second->outputToStream(out);
    out << "\\n";
  }
}
