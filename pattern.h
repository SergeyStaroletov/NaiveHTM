#ifndef __PATTERN_H
#define __PATTERN_H

#include "brain.h"
#include "stdlibs.h"

namespace brain {
struct Pattern {
  OffsetListPtr spatialPattern;
  float spatialDelta;
  float scale;
  float offset;
};
}  // namespace brain

#endif  // PATTERN_H
