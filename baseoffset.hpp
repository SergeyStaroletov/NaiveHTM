#ifndef __BASEOFFSET_HPP
#define __BASEOFFSET_HPP

#include "brain.h"
#include "stdlibs.h"

namespace brain {
template <class baseClass, enum PropertyID::Enum id,
          enum BaseDiffType::Enum diffType>
class BaseOffset : public IOffset {
 private:
  baseClass data;

 public:
  PropertyID::Enum getPropertyId() { return id; }

  void setData(baseClass data) { this->data = data; }

  baseClass getData() { return data; }

  IOffsetPtr getInverted() {
    BaseOffset<baseClass, id, diffType>* res =
        new BaseOffset<baseClass, id, diffType>();
    switch (diffType) {
      case BaseDiffType::Add: {
        res->setData(-data);
        break;
      }
      case BaseDiffType::Multiply: {
        res->setData(1.0f / data);
        break;
      }
    }
    return IOffsetPtr(res);
  }

  float getDelta(IOffsetPtr property) {
    BaseOffset<baseClass, id, diffType>* second =
        (BaseOffset<baseClass, id, diffType>*)property.get();

    float myData = data;
    float enemyData = second->getData();

    return fabs((float)(myData - enemyData));
  }

  void makeAverage(IOffsetPtr offset, float weight) {
    BaseOffset<baseClass, id, diffType>* second =
        (BaseOffset<baseClass, id, diffType>*)offset.get();
    data = (baseClass)(((float)data + weight * (float)second->getData()) /
                       (1.0f + weight));
  }

  void outputToStream(std::ostream& out) { out << (float)(data); }
};
}  // namespace brain

#endif  // BASEOFFSET_HPP
