#include <SDL.h>
#include "global.h"
#include "debug.h"
#include "playerObj.h"

// player object definitions
// =========================

playerObj::playerObj() // default constructor
{
	collidable = true;
	objType = g::OBJ_PLAYER;

	rect = g::makeRect(0, 0, 50);
}

playerObj::playerObj(const int &xPos, const int &yPos, const int &width, const int &height) // custom constructor: sets rect
{
	collidable = true;
	objType = g::OBJ_PLAYER;

	rect = g::makeRect(xPos, yPos, width, height);

	// load all keyPress images
	keypressTextures[KEY_PRESS_DEFAULT] = g::loadTexture("hello_world.bmp");
	keypressTextures[KEY_PRESS_UP] = g::loadTexture("arrows_up.bmp");
	keypressTextures[KEY_PRESS_DOWN] = g::loadTexture("arrows_down.bmp");
	keypressTextures[KEY_PRESS_LEFT] = g::loadTexture("arrows_left.bmp");
	keypressTextures[KEY_PRESS_RIGHT] = g::loadTexture("arrows_right.bmp");
}

// check for collision
g::gameObjType playerObj::checkCollisionType(gameObj &obj)
{
	// if player has no collision
	if (!collidable)
		return g::OBJ_NO_COLLISION;

	// no collision detected
	if (!SDL_HasIntersection(&rect, &obj.rect))
		return g::OBJ_NO_COLLISION;

	// prevent collision with self
	if (obj.getType() == g::OBJ_PLAYER)
		return g::OBJ_NO_COLLISION;

	return obj.getType();
}

void playerObj::checkKeystate(const std::vector<gameObj*> &collidableObjs)
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

		for (auto obj : collidableObjs)
		{
			if (checkCollisionType(*obj) != g::OBJ_WALL)
				rect.x -= 10;
		}
	}
	else if (g::keyState[SDL_SCANCODE_RIGHT])
	{
		currentTexture = keypressTextures[KEY_PRESS_RIGHT];

		for (auto obj : collidableObjs)
		{
			if (checkCollisionType(*obj) != g::OBJ_WALL)
				rect.x += 10;
		}
	}

}

// =============================
// end player object definitions
