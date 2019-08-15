#include <vector>

#include "baseObjects.h"
#include "gameObj.h"
#include "animSequence.h"


std::vector<std::vector<gameObj*>> enemyWaves = {
	// wave 1
	{
		new gameObj(baseEnemies["bat"], 200, 20, downLeft),
		new gameObj(baseEnemies["bat"], 300, 20, downRight)
	},

};
