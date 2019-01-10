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

	velocity = 10;

	// set all sides to no collision
	for (auto i : sideCollision)
		i = false;

	rect = g::makeRect(0, 0, 50);
}

// custom constructor: sets x, y, velocity, rect
playerObj::playerObj(const int &xPos, const int &yPos, const int &vel, const int &width, const int &height)
{
	collidable = true;
	objType = g::OBJ_PLAYER;

	rect = g::makeRect(xPos, yPos, width, height);

	// set all sides to no collision
	for (auto i : sideCollision)
		i = false;

	velocity = vel;

	// load all keyPress images
	keypressTextures[KEY_PRESS_DEFAULT] = g::loadTexture("hello_world.bmp");
	keypressTextures[KEY_PRESS_UP] = g::loadTexture("arrows_up.bmp");
	keypressTextures[KEY_PRESS_DOWN] = g::loadTexture("arrows_down.bmp");
	keypressTextures[KEY_PRESS_LEFT] = g::loadTexture("arrows_left.bmp");
	keypressTextures[KEY_PRESS_RIGHT] = g::loadTexture("arrows_right.bmp");
}

// check for collision
bool playerObj::checkCollision(gameObj &obj)
{  
	// if player has no collision
	if (!collidable)
		return false;

	// no collision detected
	if (!SDL_HasIntersection(&rect, &obj.rect))
	{
		// reset collisions detection sides
		for (int i = 0; i < RECT_TOTAL; i++)
			sideCollision[i] = false;

		return false;
	}

	SDL_Rect tmp;
	SDL_IntersectRect(&rect, &obj.rect, &tmp);

	// collision types
	// ===============
	if (obj.getType() == g::OBJ_BLOCK)
	{
		if (tmp.x == obj.getRectL()) // right of player
			sideCollision[RECT_R] = true;

		if (tmp.x + tmp.w == obj.getRectR()) // left of player
			sideCollision[RECT_L] = true;

		if (tmp.y + tmp.h == obj.getRectBottom()) // top of player
			sideCollision[RECT_TOP] = true;

		if (tmp.y == obj.getRectTop()) // bottom of player
			sideCollision[RECT_BOTTOM] = true;
	}

	return true;
}

void playerObj::checkKeystate()
{

	// check keystate
	//===============

	if (g::keyState[SDL_SCANCODE_UP])
	{
		currentTexture = keypressTextures[KEY_PRESS_UP];

		if (!sideCollision[RECT_TOP])
			rect.y-= velocity;
	}
	else if (g::keyState[SDL_SCANCODE_DOWN])
	{
		currentTexture = keypressTextures[KEY_PRESS_DOWN];

		if (!sideCollision[RECT_BOTTOM])
			rect.y += velocity;
	}
	else if (g::keyState[SDL_SCANCODE_LEFT])
	{
		currentTexture = keypressTextures[KEY_PRESS_LEFT];

		if (!sideCollision[RECT_L])
			rect.x -= velocity;

	}
	else if (g::keyState[SDL_SCANCODE_RIGHT])
	{
		currentTexture = keypressTextures[KEY_PRESS_RIGHT];

		if(!sideCollision[RECT_R])
			rect.x += velocity;
	}

}

// =============================
// end player object definitions
