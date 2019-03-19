#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "global.h"

// any game object
// ===============
class gameObj {
protected:
	bool collidable;
	g::gameObjType objType;

	SDL_Texture *currentTexture = nullptr;

	// rectangle sides
	enum rectSides
	{
		RECT_L,
		RECT_R,
		RECT_TOP,
		RECT_BOTTOM,
		RECT_TOTAL
	};

	// movement types
	enum moveType
	{
		MOVE_NONE,
		MOVE_R,
		MOVE_L,
		MOVE_TOTAL,
	};

public:
	gameObj(); // default constructor
	gameObj(const char textureName[], const bool &collisionBool, const g::gameObjType &objType, const int &xPos, const int &yPos, const int &width, const int &height = -1);

	~gameObj(); // destructor

	// obj rect
	SDL_Rect rect;

	// accessors
	bool isCollidable();
	g::gameObjType getType();
	SDL_Texture *getCurrentTexture();

	// get position of rect sides
	int getRectTop();
	int getRectBottom();
	int getRectL();
	int getRectR();
};
