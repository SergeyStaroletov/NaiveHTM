#include "utils.h"

using namespace std;
using namespace brain;

int getNumberOfOccurrences(const HypothesisPtr big, const HypothesisPtr small) {
  /*




      int result = 0;
      int j = 0;
      for (unsigned int i = 0; i < big->size(); i++)
      {
          if (big[i] == small[j])
              result++;
          if (j == small->size())
              j = 0;
      }
      return result;*/
  return 0;
}

Timestamp Utils::abs(Timestamp a) {
  if (a < 0) return -a;
  return a;
}
