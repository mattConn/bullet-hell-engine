#include <vector>
#include <utility>

#include "gameObj.h"

typedef std::vector<bool (*)(gameObj*)> moveVector;
typedef std::pair<moveVector, int> movePair;
