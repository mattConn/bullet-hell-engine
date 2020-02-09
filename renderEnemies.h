#pragma once

#include <vector>
#include "global.h"
#include "gameObj.h"

void renderEnemies(std::vector<gameObj> &enemies, std::vector<gameObj> &bullets)
{
	// render all current objs
			// =======================
	for (int i = 0; i < enemies.size(); i++)
	{
		if (!enemies[i].isOffscreen()) // if not offscreen
		{
			// render
			global::render(enemies[i].currentTexture, &enemies[i].rect);

			// play animations
			enemies[i].playAnimations();
				
			// check for player bullet collision
			for (int j = 0; j < bullets.size(); j++)
			{
				if (SDL_HasIntersection(&enemies[i].rect, &bullets[j].rect))
				{
					enemies.erase(enemies.begin() + i);

					bullets.erase(bullets.begin() + j);

					global::kills++;
					break; // avoid out of range index
				}
			}
		}
		else // offscreen: remove
		{
			enemies.erase(enemies.begin() + i);
		}
	}
}
