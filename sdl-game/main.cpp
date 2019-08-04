#include <iostream>
#include <vector>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#undef main

#include "debug.h"
#include "global.h"
#include "bulletContainers.h"
#include "animation.h"
#include "gameObj.h"

#include "getPlayerInput.h"
#include "renderEnemies.h"
#include "renderBullets.h"
#include "hasMiddleCollision.h"


int main(int argc, char* argv[])
{
	// init sdl
	if (!global::init(global::window, global::windowSurface))
	{
		DEBUG_MSG("Init failed");
		return -1;
	}

	// hide cursor
	SDL_ShowCursor(SDL_DISABLE);

	// containers
	// ==========

	// load textures
	global::allTextures["enemy"] = global::loadTexture("enemy.png");
	global::allTextures["player"] = global::loadTexture("player.png");
	global::allTextures["player-bullet"] = global::loadTexture("player-bullet.png");

	// list of all objects
	std::vector<gameObj*> currentEnemies = {
		new gameObj("enemy", 10, 500, 10, 50, 50),
		new gameObj("enemy", 10, 600, 50, 50, 50),
		new gameObj("enemy", 10, 400, 20, 50, 50),
	};

	for(auto i : currentEnemies)
	{
		i->setAnimation(animation::wait);
		i->setBullet("player-bullet", 10, 20, 20, 100);
	}


	// make player 
	// ===========

	// construct player
	gameObj player = gameObj("player", 10, global::SCREEN_WIDTH / 2 - 10 / 2, global::SCREEN_HEIGHT / 2 - 100 / 2, 50, 85);

	// set player bullet properties
	player.setBullet("player-bullet", -10, 20, 20, 100);

	// game state booleans
	bool quit = false;
	bool paused = false;

	// event handler
	SDL_Event event;

	// realtime keystate
	const Uint8* keyState = SDL_GetKeyboardState(nullptr);

	// player life state bools
	bool playerIsDead = false;
	bool playerIsInvulnerable = false;
	
	// player life timeouts
	int playerDeathTimeout;
	int playerInvulnerableTimeout;

	// scorekeeping
	int deaths = 0;
	int graze = 0;

	// game loop
	//===========
	while (!quit)
	{
		// event polling loop
		while (SDL_PollEvent(&event))
		{
			// window close event
			if (event.type == SDL_QUIT)
			{
				quit = true;
				break;
			}

			// keyboard events
			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE: // pause
					paused = paused ? false : true;
					break;

				case SDLK_RETURN: // quit
					quit = true;
					break;
				}
			} // end get keyboard events
		} // end poll events


		// run when not paused
		if (!paused)
		{
			// render scene
			// ============

			// update window
			SDL_RenderClear(global::renderer);

			// player alive routine (render player, enemy bullets)
			// ===================================================
			if (!playerIsDead)
			{
				playerDeathTimeout = SDL_GetTicks() + 500; // keep updating death timeout

				// get input
				getPlayerInput(player, keyState);

				// enemies fire bullets
				for (auto i : currentEnemies)
					animation::fire(i);

				// render bullets
				// =========================
				renderBullets(currentPlayerBullets);
				renderBullets(currentEnemyBullets);

				// render player
				if (playerIsInvulnerable) // check invulnerability after respawn
					animation::blink(&player);
				else
					global::render(player.getCurrentTexture(), player.getRectPtr());

				// check for enemy bullet collision (hitbox is player middle)
				if(!playerIsInvulnerable && hasMiddleCollision(player, currentEnemyBullets))
				{
					playerIsDead = true;
					deaths++;
				}
			}
			else
			{
				// dead, delay between respawn
				// ===========================

				playerInvulnerableTimeout = SDL_GetTicks() + 1000; // update invulnerability timeout

				currentEnemyBullets.clear(); // remove bullets

				// player comes back
				if (SDL_TICKS_PASSED(SDL_GetTicks(), playerDeathTimeout))
				{
					playerIsDead = false;
					playerIsInvulnerable = true;
				}
			}

			// spawn protection
			if (playerIsInvulnerable && SDL_TICKS_PASSED(SDL_GetTicks(), playerInvulnerableTimeout))
				playerIsInvulnerable = false;

			// render enemies
			renderEnemies(currentEnemies, currentPlayerBullets);

		} // end if not paused block

		SDL_RenderPresent(global::renderer);

		SDL_Delay(16);
	}

	//==============
	// end game loop

	// close SDL subsystems
	global::close();
	std::cout << "** Gameplay stats **" << std::endl;
	std::cout << "Deaths: " << deaths << std::endl;
	std::cout << "Graze: " << graze << std::endl;

	return 0;
}
