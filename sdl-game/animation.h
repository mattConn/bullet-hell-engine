#pragma once

#include "gameObj.h"

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
		if (abs(g->getInitialY() - g->getRectY()) < 100)
			g->incRectY(5);
		else
			g->decRectX(5);

		return endAnimation(g);
	}
}