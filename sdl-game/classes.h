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

	SDL_Texture *currentTexture = nullptr;

public:
	gameObj(); // default constructor
	gameObj(const bool &collisionBool, const gameObjType &objType, const int &xPos, const int &yPos, const int &width, const int &height = -1);

	// obj rect
	SDL_Rect rect;

	// accessors
	bool isCollidable();
	gameObjType getType();
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

	void checkKeystate();
};