#ifndef __BASEPROPERTY_HPP
#define __BASEPROPERTY_HPP

#include "brain.h"
#include "stdlibs.h"

namespace brain {
template <class baseClass, enum PropertyID::Enum id,
          enum BaseDiffType::Enum diffType>
class BaseProperty : public IProperty {
 private:
  baseClass data;

 public:
  PropertyID::Enum GetId() { return id; }

  void setData(baseClass data) { this->data = data; }

  baseClass getData() { return data; }

  IPropertyPtr createByOffset(IOffsetPtr offset) {
    BaseOffset<baseClass, id, diffType>* second =
        (BaseOffset<baseClass, id, diffType>*)offset.get();
    boost::shared_ptr<BaseProperty<baseClass, id, diffType> > result(
        new BaseProperty<baseClass, id, diffType>());
    switch (diffType) {
      case BaseDiffType::Add: {
        result->setData(data + second->getData());
        break;
      }
      case BaseDiffType::Multiply: {
        result->setData(data * second->getData());
        break;
      }
    }
    return result;
  }

  IOffsetPtr createOffset(IPropertyPtr property) {
    if (property->GetId() != id) throw "Different property IDs!";
    baseClass resultData;
    switch (diffType) {
      case BaseDiffType::Add: {
        resultData =
            (baseClass)((BaseProperty*)(property.get()))->getData() - data;
        break;
      }
      case BaseDiffType::Multiply: {
        resultData =
            (baseClass)((BaseProperty*)(property.get()))->getData() / data;
        break;
      }
    }
    BaseOffset<baseClass, id, diffType>* temp =
        new BaseOffset<baseClass, id, diffType>();
    temp->setData(resultData);
    return IOffsetPtr(temp);
  }

  float getDelta(IPropertyPtr property) {
    BaseProperty<baseClass, id, diffType>* second =
        (BaseProperty<baseClass, id, diffType>*)property.get();
    return fabs((float)(data - second->getData()));
  }
};
}  // namespace brain

#endif  // BASEPROPERTY_HPP
