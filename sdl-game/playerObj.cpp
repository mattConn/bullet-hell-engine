#include <SDL2/SDL.h>
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

    // load all keyPress images
    keypressTextures[KEY_PRESS_DEFAULT] = g::loadTexture("hello_world.bmp");
    keypressTextures[KEY_PRESS_UP] = g::loadTexture("arrows_up.bmp");
    keypressTextures[KEY_PRESS_DOWN] = g::loadTexture("arrows_down.bmp");
    keypressTextures[KEY_PRESS_LEFT] = g::loadTexture("arrows_left.bmp");
    keypressTextures[KEY_PRESS_RIGHT] = g::loadTexture("arrows_right.bmp");

    currentTexture = keypressTextures[KEY_PRESS_LEFT];
}

// custom constructor: sets x, y, velocity, rect
playerObj::playerObj(const int &xPos, const int &yPos, const int &vel, const int &width, const int &height, const KeyPresses &direction) : playerObj()
{
    rect = g::makeRect(xPos, yPos, width, height);
    velocity = vel;

    currentTexture = keypressTextures[direction];
}


// wrapper for player state functions
void playerObj::getUserInput(std::vector<gameObj*>& objVector)
{

	// move left
	if (g::keyState[SDL_SCANCODE_LEFT] && !sideCollision[RECT_L])
	{
		checkCollision(objVector);
		currentTexture = keypressTextures[KEY_PRESS_LEFT];
		updateWorldPosition(objVector, velocity);
	}

	// move right
	if (g::keyState[SDL_SCANCODE_RIGHT] && !sideCollision[RECT_R])
	{
		checkCollision(objVector);
		currentTexture = keypressTextures[KEY_PRESS_RIGHT];
		updateWorldPosition(objVector, -velocity);
	}

	// move up
	if (g::keyState[SDL_SCANCODE_UP] && !sideCollision[RECT_TOP])
	{
		checkCollision(objVector);
		currentTexture = keypressTextures[KEY_PRESS_UP];
		updateWorldPosition(objVector, 0, velocity);
	}

	// move down
	if (g::keyState[SDL_SCANCODE_DOWN] && !sideCollision[RECT_BOTTOM])
	{
		checkCollision(objVector);
		currentTexture = keypressTextures[KEY_PRESS_DOWN];
		updateWorldPosition(objVector, 0, -velocity);
	}
}

void playerObj::updateWorldPosition(std::vector<gameObj*>& objVector, const int x, const int y)
{
	for (auto obj : objVector)
	{
		obj->incRectX(x);
		obj->incRectY(y);
	}
}

void playerObj::checkCollision(std::vector<gameObj*>& objVector)
{
	resetCollision();

	for (auto obj : objVector)
	{
		SDL_Rect intersection; // intersection rect

		if (SDL_IntersectRect(&rect, &obj->rect, &intersection))
		{
			if (intersection.y <= getRectTop()) // top collision
				sideCollision[RECT_TOP] = true;

			if (intersection.y + intersection.h >= getRectBottom()) // bottom collision
				sideCollision[RECT_BOTTOM] = true;

			if (intersection.x <= getRectL()) // left collision
				sideCollision[RECT_L] = true;

			if (intersection.x + intersection.w >= getRectR()) // right collision
				sideCollision[RECT_R] = true;
		}
	} // end foreach
}

void playerObj::resetCollision()
{
	for (int i = 0; i < RECT_TOTAL; i++)
		sideCollision[i] = false;
}
// =============================
// end player object definitions
