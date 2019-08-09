#include <map>
#include <string>
#include "gameObj.h"

// all bullet types in game
// ========================

std::map<std::string, gameObj> allBullets = {
	{"red", gameObj("bullet-red", 10, 0, 0, 20, 20, nullptr, 100)},
	{"orange", gameObj("bullet-orange", 10, 0, 0, 20, 20, nullptr, 500)},
};
