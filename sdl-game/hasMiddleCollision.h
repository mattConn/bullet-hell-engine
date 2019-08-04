#pragma once

#include <vector>
#include <SDL2/SDL.h>
#include "gameObj.h"

bool hasMiddleCollision(gameObj& obj, std::vector<gameObj> &objVec)
{
	// check for enemy bullet collision (hitbox is obj middle)
	for (int i = 0; i < objVec.size(); i++)
	{
		gameObj intersection; // store intersection

		// check collision
		if (SDL_IntersectRect(objVec[i].getRectPtr(), obj.getRectPtr(), intersection.getRectPtr()))
		{
			// check middle collision
			if (intersection.getRectX() <= obj.getRectMiddle() && intersection.getRectR() >= obj.getRectMiddle())
				return true;
		}
	}

	return false;
}