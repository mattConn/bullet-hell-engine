#include <vector>

#include "animation.h"
#include "gameObj.h"

namespace enemy {
	gameObj *bat = new gameObj("enemy-bat", 8, 0, 0, 50, 46, new gameObj("bullet-orange", 7, 20, 20, 500));
}

std::vector<std::vector<gameObj*>> enemyWaves = {
	// wave 1
	{
		new gameObj(enemy::bat, 10, 20),
		new gameObj("enemy-bat", 8, 400, 10, 50, 46, new gameObj("bullet-orange", 7, 20, 20, 500),
			{
				{ { animation::down, animation::left, animation::fire }, 100},
				{ { animation::down }, 100},
				{ { animation::down, animation::right, animation::fire }, 100},
				{ { animation::up, animation::right}, 100},
				{ { animation::down } , 0}
			}
		),
		new gameObj("enemy-bat", 8, 300, 10, 50, 46, new gameObj("bullet-orange", 7, 20, 20, 500),
			{
				{ { animation::down, animation::left, animation::fire }, 100},
				{ { animation::down }, 100},
				{ { animation::down, animation::right, animation::fire }, 100},
				{ { animation::up, animation::right}, 100},
				{ { animation::down } , 0}
			}
		),
	},

	// wave 2
	{
		new gameObj("enemy-bat", 8, 500, 10, 50, 46, new gameObj("bullet-orange", 7, 20, 20, 500),
			{
				{ { animation::down, animation::left, animation::fire }, 100},
				{ { animation::down }, 100},
				{ { animation::down, animation::right, animation::fire }, 100},
				{ { animation::up, animation::right}, 100},
				{ { animation::down } , 0}
			}
		),
		new gameObj("enemy-bat", 5, 600, 50, 50, 46),
		new gameObj("enemy-bat", 5, 400, 20, 50, 46)
	}

};
