// default constructor
#include "classes.h"

// game object definitions
// =======================

// rect making helper function
SDL_Rect gameObj::makeRect(const int &xPos, const int &yPos, const int &width, const int &height)
{
	SDL_Rect rect;
	rect.x = xPos;

	rect.y = yPos;
	rect.w = width;
	rect.h = height == -1 ? width : height;

	return rect;
}

// default constructor
gameObj::gameObj()
{
	collidable = false;
	objType = OBJ_GRAPHIC;

	rect = makeRect(0.0, 0.0, 1.0);
}

// custom constructor
// set collision, obj type, rect data
gameObj::gameObj(const bool &collisionBool, const gameObjType &oType, const int &xPos, const int &yPos, const int &width, const int &height)
{
	collidable = collisionBool;
	objType = oType;

	rect = makeRect(xPos, yPos, width, height);
}

inline bool gameObj::isCollidable()
{
	return collidable;
}

inline gameObjType gameObj::getType()
{
	return objType;
}


// ===========================
// end game object definitions

// player object definitions
// =========================

playerObj::playerObj() // default constructor
{
	collidable = true;
	objType = OBJ_PLAYER;

	rect = makeRect(0, 0, 50);
}

playerObj::playerObj(const int &xPos, const int &yPos, const int &width, const int &height) // custom constructor: sets rect
{
	collidable = true;
	objType = OBJ_PLAYER;

	rect = makeRect(xPos, yPos, width, height);
}


// =============================
// end player object definitions
