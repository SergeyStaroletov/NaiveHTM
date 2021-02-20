#ifndef __LINK_H
#define __LINK_H

#include "brain.h"
#include "stdlibs.h"

namespace brain {
struct Link {
  OffsetListPtr offsets;
  int amount;
};
}  // namespace brain
#endif  // LINK_H
