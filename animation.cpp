#include "global.h"
#include "gameObj.h"
#include "animation.h"
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
		if (SDL_TICKS_PASSED(SDL_GetTicks(), g->timeout))
		{
			currentEnemyBullets.push_back(g->getBulletCopy());
			g->resetTimeout();
		}
		return true;
	}

	bool up(gameObj *g)
	{
		g->rect.y -= g->velocity;
	
		return true;
	}

	bool down(gameObj *g)
	{
		g->rect.y += g->velocity;
	
		return true;
	}

	bool left(gameObj *g)
	{
		g->rect.y -= g->velocity;
	
		return true;
	}

	bool right(gameObj *g)
	{
		g->rect.x += g->velocity;
	
		return true;
	}

	bool downAndLeft(gameObj *g)
	{

		if (abs(g->initialY - g->rect.y) < 100)
			g->rect.y += 5;
		else
			g->rect.x -= 5;

		return true;
	}

	bool blink(gameObj* g)
	{
		if (SDL_GetTicks() & 1) // render on odd tick (blink)
			global::render(g->currentTexture, &g->rect);

		return true;
	}
}
