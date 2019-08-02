#pragma once

#include "gameObj.h"
#include "bulletContainers.h"

namespace animation {
	bool endAnimation(const gameObj* g)
	{
		if (g->isOffscreen())
			return false;
		else
			return true;
	}

	bool downAndLeft(gameObj *g)
	{
		if (SDL_TICKS_PASSED(SDL_GetTicks(), g->getBulletPtr()->getTimeout()))
		{
			currentEnemyBullets.push_back(g->getBulletCopy());
			g->getBulletPtr()->resetTimeout();
		}

		
		if (abs(g->getInitialY() - g->getRectY()) < 100)
			g->incRectY(5);
		else
			g->decRectX(5);

		return endAnimation(g);
	}
}
