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
	
	bool wait(gameObj* g)
	{
		return true;
	}

	bool fire(gameObj* g)
	{
		if (SDL_TICKS_PASSED(SDL_GetTicks(), g->getBulletPtr()->getTimeout()))
		{
			currentEnemyBullets.push_back(g->getBulletCopy());
			g->getBulletPtr()->resetTimeout();
		}
		return true;
	}

	bool downAndLeft(gameObj *g)
	{

		if (abs(g->getInitialY() - g->getRectY()) < 100)
			g->incRectY(5);
		else
			g->decRectX(5);

		return endAnimation(g);
	}

	bool blink(gameObj* g)
	{
		if (SDL_GetTicks() & 1) // render on odd tick (blink)
			SDL_RenderCopy(global::renderer, global::allTextures[g->getCurrentTexture()], nullptr, g->getRectPtr());

		return true;
	}
}
