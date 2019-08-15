#include <vector>
#include <map>
#include <string>

#include "baseObjects.h"
#include "animation.h"
#include "gameObj.h"

std::vector<std::vector<gameObj*>> enemyWaves = {
	// wave 1
	{
		new gameObj(baseEnemies["bat"], 10, 20)
	},

};
