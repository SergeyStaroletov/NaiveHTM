#ifndef __IProperty_h__
#define __IProperty_h__

#include "brain.h"
#include "stdlibs.h"

namespace brain
{
    class IProperty
    {
    public:
        virtual PropertyID::Enum GetId() = 0;
        virtual IPropertyPtr createByOffset(IOffsetPtr offset) = 0;
        virtual IOffsetPtr createOffset(IPropertyPtr property) = 0;
        virtual float getDelta(IPropertyPtr property) = 0;
    };
}
#endif
