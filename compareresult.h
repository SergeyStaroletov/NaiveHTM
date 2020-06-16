#ifndef __COMPARERESULT_H
#define __COMPARERESULT_H

#include "brain.h"
#include "stdlibs.h"

namespace brain {
struct CompareResult {
  float delta;
  std::vector<LinkPtr> assignation;
};
}  // namespace brain

#endif  // COMPARERESULT_H
