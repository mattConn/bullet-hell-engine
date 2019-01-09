// default constructor
#include <SDL.h>
#include "global.h"
#include "debug.h"
#include "classes.h"

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
	objType = OBJ_GRAPHIC;

	rect = g::makeRect(0, 0, 1);
}

// custom constructor
// set collision, obj type, rect data
gameObj::gameObj(const bool &collisionBool, const gameObjType &oType, const int &xPos, const int &yPos, const int &width, const int &height)
{
	collidable = collisionBool;
	objType = oType;

	rect = g::makeRect(xPos, yPos, width, height);
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

	rect = g::makeRect(0, 0, 50);
}

playerObj::playerObj(const int &xPos, const int &yPos, const int &width, const int &height) // custom constructor: sets rect
{
	collidable = true;
	objType = OBJ_PLAYER;

	rect = g::makeRect(xPos, yPos, width, height);

	// load all keyPress images
	keypressTextures[KEY_PRESS_DEFAULT] = g::loadTexture("hello_world.bmp");
	keypressTextures[KEY_PRESS_UP] = g::loadTexture("arrows_up.bmp");
	keypressTextures[KEY_PRESS_DOWN] = g::loadTexture("arrows_down.bmp");
	keypressTextures[KEY_PRESS_LEFT] = g::loadTexture("arrows_left.bmp");
	keypressTextures[KEY_PRESS_RIGHT] = g::loadTexture("arrows_right.bmp");
}

void playerObj::checkKeystate()
{
	// check keystate
	//===============

	if (g::keyState[SDL_SCANCODE_UP])
	{
		currentTexture = keypressTextures[KEY_PRESS_UP];

		if (SDL_HasIntersection(&rect, &g::screenEdge[g::SCREEN_EDGE_TOP]))
			rect.y = g::SCREEN_HEIGHT - rect.h;
		else
			rect.y -= 10;
	}
	else if (g::keyState[SDL_SCANCODE_DOWN])
	{
		currentTexture = keypressTextures[KEY_PRESS_DOWN];

		if (SDL_HasIntersection(&rect, &g::screenEdge[g::SCREEN_EDGE_BOTTOM]))
			rect.y = 0;
		else
			rect.y += 10;
	}
	else if (g::keyState[SDL_SCANCODE_LEFT])
	{
		currentTexture = keypressTextures[KEY_PRESS_LEFT];

		if (SDL_HasIntersection(&rect, &g::screenEdge[g::SCREEN_EDGE_LEFT]))
			rect.x = g::SCREEN_WIDTH - rect.w;
		else
			rect.x -= 10;
	}
	else if (g::keyState[SDL_SCANCODE_RIGHT])
	{
		currentTexture = keypressTextures[KEY_PRESS_RIGHT];

		if (SDL_HasIntersection(&rect, &g::screenEdge[g::SCREEN_EDGE_RIGHT]))
			rect.x = 0;
		else
			rect.x += 10;
	}

}

// =============================
// end player object definitions
