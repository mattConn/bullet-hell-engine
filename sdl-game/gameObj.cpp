#include <SDL.h>
#include "global.h"
#include "debug.h"
#include "gameObj.h"

// game object definitions
// =======================

SDL_Texture *gameObj::getCurrentTexture()
{
	return currentTexture;
}

// default constructor
gameObj::gameObj()
{
	collidable = false;
	objType = g::OBJ_GRAPHIC;

	rect = g::makeRect(0, 0, 1);
}

// custom constructor
// set collision, obj type, rect data
gameObj::gameObj(const bool &collisionBool, const g::gameObjType &oType, const int &xPos, const int &yPos, const int &width, const int &height)
{
	collidable = collisionBool;
	objType = oType;

	rect = g::makeRect(xPos, yPos, width, height);
}

// destructor
gameObj::~gameObj()
{
	SDL_DestroyTexture(currentTexture);
	currentTexture = nullptr;
}

inline bool gameObj::isCollidable()
{
	return collidable;
}

g::gameObjType gameObj::getType()
{
	return objType;
}


// ===========================
// end game object definitions