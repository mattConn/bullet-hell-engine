#include <vector>

#include "baseObjects.h"
#include "gameObj.h"
#include "animation.h"
#include "animSequence.h"

using namespace animation;

std::vector<std::vector<gameObj*>> enemyWaves = {
	// wave 1
	{
		new gameObj(baseEnemies["bat"], 200, 20,
		{
			{{down, left, fire}, 200},
			{{down, fire}, 0},
		}
		),
		new gameObj(baseEnemies["bat"], 300, 20, {
			{{right, fire}, 200},
			{{left, fire}, 200},
			{{right, fire}, 200},
			{{left, fire}, 200},
			{{right, fire}, 200},
			{{left, fire}, 200},
			{{down, fire}, 0}
		})
	},

};
