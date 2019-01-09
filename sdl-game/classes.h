#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "global.h"
#include <vector>

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

// player object
// =============
class playerObj : public gameObj {

	// keypress enum for relating textures to keypress events
	enum KeyPresses
	{
		KEY_PRESS_DEFAULT,
		KEY_PRESS_UP,
		KEY_PRESS_DOWN,
		KEY_PRESS_LEFT,
		KEY_PRESS_RIGHT,
		KEY_PRESS_TOTAL
	};

	// textures for keypresses
	SDL_Texture *keypressTextures[KEY_PRESS_TOTAL];

public:
	playerObj(); // default constructor
	playerObj(const int &xPos, const int &yPos, const int &width, const int &height = -1);

	g::gameObjType checkCollisionType(gameObj &obj); // check for collision

	void checkKeystate(const std::vector<gameObj*> &collidableObjs); // check keystate
};