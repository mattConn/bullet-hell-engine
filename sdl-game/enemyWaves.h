#include <vector>
#include <map>
#include <string>

#include "baseObjects.h"
#include "animation.h"
#include "gameObj.h"

// base objects to copy
std::map<std::string, gameObj*> baseBullets = {
	{
		"orange",
		new gameObj("bullet-orange", 7, 20, 20, 500)
	},

	{
		"red",
		new gameObj("bullet-red", -10, 20, 20, 100)
	}
};
std::map<std::string, gameObj*> baseEnemies = {
	{
		"bat",
		new gameObj("enemy-bat", 8, 0, 0, 50, 46, baseBullets["orange"])
	}
};

std::vector<std::vector<gameObj*>> enemyWaves = {
	// wave 1
	{
		new gameObj(baseEnemies["bat"], 10, 20)
	},

};
