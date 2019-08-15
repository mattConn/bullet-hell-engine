#include <vector>
#include <map>
#include <string>

#include "baseObjects.h"
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

std::vector<std::vector<gameObj*>> enemyWaves = {
	// wave 1
	{
		new gameObj(baseEnemies["bat"], 200, 20, downLeft),
		new gameObj(baseEnemies["bat"], 300, 20, downRight)
	},

};
