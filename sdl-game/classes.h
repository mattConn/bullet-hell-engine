#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

// obj types
enum gameObjType
{
	OBJ_PLATFORM,
	OBJ_PLAYER,
	OBJ_ENEMY,
	OBJ_GRAPHIC,
	OBJ_TOTAL
};

// any game object
// ===============
class gameObj {
protected:
	bool collidable;
	gameObjType objType;

	// rect making helper function
	SDL_Rect makeRect(const int &xPos, const int &yPos, const int &width, const int &height = -1);

public:
	gameObj(); // default constructor
	gameObj(const bool &collisionBool, const gameObjType &objType, const int &xPos, const int &yPos, const int &width, const int &height = -1);

	// obj rect
	SDL_Rect rect;

	// accessors
	bool isCollidable();
	gameObjType getType();

};

// player object
// =============
class playerObj : public gameObj {

public:
	playerObj(); // default constructor
	playerObj(const int &xPos, const int &yPos, const int &width, const int &height = -1);
};