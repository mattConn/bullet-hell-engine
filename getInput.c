#include "global.h"
#include "getInput.h"
#include "gameObj.h"
#include <stdio.h>
#include <SDL2/SDL.h>

void getInput(gameObj* player, const Uint8* keyState)
{
	// player keybindings
	// ==================
	// slow down
	if (keyState[SDL_SCANCODE_LSHIFT])
		player->velocityMod = .35;
	else
		player->velocityMod = 1;

	// fire
	/*
	if (keyState[SDL_SCANCODE_Z] && SDL_TICKS_PASSED(SDL_GetTicks(), player.getBulletPtr()->getTimeout()))
	{
		currentPlayerBullets.push_back(player.getBulletCopy());
		player.getBulletPtr()->resetTimeout();
	}
	*/

	// move left
	if (keyState[SDL_SCANCODE_LEFT] && player->rect.x > 0)
		player->rect.x += -player->velocity * player->velocityMod;

	// move right
	if (keyState[SDL_SCANCODE_RIGHT] && player->rect.x + player->rect.w < SCREEN_WIDTH)
		player->rect.x += player->velocity * player->velocityMod;

	// move up
	if (keyState[SDL_SCANCODE_UP] && player->rect.y > 0)
		player->rect.y += -player->velocity * player->velocityMod;

	// move down
	if (keyState[SDL_SCANCODE_DOWN] && player->rect.y + player->rect.h < SCREEN_HEIGHT)
		player->rect.y += player->velocity * player->velocityMod;
}
