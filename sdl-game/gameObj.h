#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "global.h"

// any game object
// ===============
class gameObj {
protected:
	bool collidable;
	g::gameObjType objType;

	SDL_Texture *currentTexture = nullptr;

public:
	gameObj(); // default constructor
	gameObj(const bool &collisionBool, const g::gameObjType &objType, const int &xPos, const int &yPos, const int &width, const int &height = -1);

	~gameObj(); // destructor

	// obj rect
	SDL_Rect rect;

	// accessors
	bool isCollidable();
	g::gameObjType getType();
	SDL_Texture *getCurrentTexture();

};