#include <vector>
#include <utility>

#include "animation.h"
#include "gameObj.h"


typedef std::vector<bool (*)(gameObj*)> animVector;
typedef std::pair<animVector, int> animPair;

using namespace animation;

std::vector<animPair> downLeft = {
	{{down, left}, 200},
	{{down}, 0}
};

std::vector<animPair> downRight = {
	{{down, right}, 200},
	{{down}, 0}
};
