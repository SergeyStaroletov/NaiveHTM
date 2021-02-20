#ifndef __Utils_h__
#define __Utils_h__


#include "brain.h"
#include "stdlibs.h"

namespace brain
{
    class Utils
    {
    public:
		static int getNumberOfOccurrences(const HypothesisPtr big, const HypothesisPtr small);
        static Timestamp abs(Timestamp a);
    };
}
#endif
