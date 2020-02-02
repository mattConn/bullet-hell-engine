#pragma once

#include <vector>
#include "global.h"
#include "gameObj.h"

void renderBullets(std::vector<gameObj> &bullets)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		// translate
		bullets[i].rect.y += bullets[i].velocity;

		// remove bullet if offscreen
		if (bullets[i].isOffscreen())
			bullets.erase(bullets.begin() + i);
		else
			//render bullet
			global::render(bullets[i].currentTexture, &bullets[i].rect);
	}
}
