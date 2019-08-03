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
		player.setVelocityMod(.35);
	else
		player.setVelocityMod(1);

	// fire
	if (keyState[SDL_SCANCODE_Z] && SDL_TICKS_PASSED(SDL_GetTicks(), player.getBulletPtr()->getTimeout()))
	{
		currentPlayerBullets.push_back(player.getBulletCopy());
		player.getBulletPtr()->resetTimeout();
	}

	// move left
	if (keyState[SDL_SCANCODE_LEFT] && player.getRectL() > 0)
		player.incRectX(-player.getVelocity() * player.getVelocityMod());

	// move right
	if (keyState[SDL_SCANCODE_RIGHT] && player.getRectR() < global::SCREEN_WIDTH)
		player.incRectX(player.getVelocity() * player.getVelocityMod());

	// move up
	if (keyState[SDL_SCANCODE_UP] && player.getRectTop() > 0)
		player.incRectY(-player.getVelocity() * player.getVelocityMod());

	// move down
	if (keyState[SDL_SCANCODE_DOWN] && player.getRectBottom() < global::SCREEN_HEIGHT)
		player.incRectY(player.getVelocity() * player.getVelocityMod());
}