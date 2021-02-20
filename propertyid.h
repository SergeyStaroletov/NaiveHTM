#ifndef __PropertyID_h__
#define __PropertyID_h__


#include "brain.h"
#include "stdlibs.h"

namespace brain
{
    namespace PropertyID
    {
        enum Enum
        {
            Tone,
            Velocity,
            DrumsID,
            InstrumentID,
            Time,
            HyperSensorId,
            Channel
        };
    }

    namespace HyperSensor
    {
        enum Enum
        {
            Piano,
            Drums,
            Methronome
        };
    }


}

#endif
