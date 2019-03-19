#include <SDL2/SDL.h>
#include "global.h"
#include "debug.h"
#include "gameObj.h"

// game object definitions
// =======================

SDL_Texture *gameObj::getCurrentTexture()
{
	return currentTexture;
}

// get rect sides
int gameObj::getRectTop(){ return rect.y; }
int gameObj::getRectBottom(){ return rect.y + rect.h; }
int gameObj::getRectL() { return rect.x; }
int gameObj::getRectR() { return rect.x + rect.w; }

// default constructor
gameObj::gameObj()
{
	collidable = false;
	objType = g::OBJ_GRAPHIC;

	rect = g::makeRect(0, 0, 1);
}

// custom constructor
// set collision, obj type, rect data
gameObj::gameObj(const char textureName[], const bool &collisionBool, const g::gameObjType &oType, const int &xPos, const int &yPos, const int &width, const int &height)
{
	currentTexture = g::loadTexture(textureName);
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

bool gameObj::isCollidable()
{
	return collidable;
}

g::gameObjType gameObj::getType()
{
	return objType;
}


// ===========================
// end game object definitions
