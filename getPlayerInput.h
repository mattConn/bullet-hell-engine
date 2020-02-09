#pragma once

#include "global.h"
#include "gameObj.h"
#include "bulletContainers.h"
#include <SDL2/SDL.h>

void getPlayerInput(gameObj& player, const Uint8* keyState)
{
	// player keybindings
	// ==================
	// slow down
	if (keyState[SDL_SCANCODE_LSHIFT])
		player.velocityMod = (.35);
	else
		player.velocityMod = (1);

	// fire
	if (keyState[SDL_SCANCODE_Z] && SDL_TICKS_PASSED(SDL_GetTicks(), player.timeout))
	{
		global::shotsFired++;
		currentPlayerBullets.push_back(player.getBulletCopy());
		player.resetTimeout();
	}

	// move left
	if (keyState[SDL_SCANCODE_LEFT] && player.getRectL() > 0)
	{
		global::distanceTraveled++;
		player.rect.x += -player.velocity * player.velocityMod;
	}

	// move right
	if (keyState[SDL_SCANCODE_RIGHT] && player.getRectR() < global::SCREEN_WIDTH)
	{
		global::distanceTraveled++;
		player.rect.x += player.velocity * player.velocityMod;
	}

	// move up
	if (keyState[SDL_SCANCODE_UP] && player.getRectTop() > 0)
	{
		global::distanceTraveled++;
		player.rect.y += -player.velocity * player.velocityMod;
	}

	// move down
	if (keyState[SDL_SCANCODE_DOWN] && player.getRectBottom() < global::SCREEN_HEIGHT)
	{
		global::distanceTraveled++;
		player.rect.y += player.velocity * player.velocityMod;
	}
}
