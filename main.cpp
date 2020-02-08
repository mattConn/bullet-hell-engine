#include <iostream>
#include <vector>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#undef main

#include "debug.h"
#include "global.h"
#include "bulletContainers.h"
#include "baseObjects.h"
#include "enemyWaves.h"
#include "movement.h"
#include "gameObj.h"
#include "configFromFile.h"

#include "getPlayerInput.h"
#include "renderEnemies.h"
#include "renderBullets.h"

int main(int argc, char* argv[])
{
	// init sdl
	if (!global::init(global::window, global::windowSurface))
	{
		DEBUG_MSG("Init failed");
		return -1;
	}

	// containers
	// ==========

	// load textures
	global::allTextures["player"] = global::loadTexture("player.png");
	global::allTextures["cloud-bg"] = global::loadTexture("cloud-bg.png");
	global::allTextures["hitbox"] = global::loadTexture("hitbox.png");

	DEBUG_MSG("Loading Bullets:");
	// load bullets from file
	bulletsFromFile("config/bullets.conf", baseBullets);	

	DEBUG_MSG("Loading Enemies:");
	// enemies from file
	enemiesFromFile("config/enemies.conf", baseEnemies);

	DEBUG_MSG("Loading Waves:");
	// enemies from file
	wavesFromFile("config/waves.conf", enemyWaves);

/*
std::vector<std::vector<gameObj*>> enemyWaves = {
	// wave 1
	{
		new gameObj(baseEnemies["bat"], 200, 20,
		{
			{{down, left, fire}, 200},
			{{down, fire}, 0},
		}
		),
		new gameObj(baseEnemies["bat"], 300, 20, {
			{{right, fire}, 200},
			{{left, fire}, 200},
			{{right, fire}, 200},
			{{left, fire}, 200},
			{{right, fire}, 200},
			{{left, fire}, 200},
			{{down, fire}, 0}
		})
	},

};
*/


	// make player 
	// ===========

	// construct player
	gameObj player = gameObj("player", 8, 50, 85, global::SCREEN_WIDTH / 2 - 10 / 2, global::SCREEN_HEIGHT / 2 - 100 / 2, "red", 100);
	gameObj hitbox = gameObj("hitbox", player.velocity, 10, 10);

	// set background
	gameObj bg = gameObj("cloud-bg", 5, 800, 600);
	SDL_Rect bgRect = bg.rect; // rect for 2nd bg render
	bgRect.y = -bg.rect.h;

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


		// skip scene updating when paused
		if (paused) goto renderPresent;

		// update scene
		// ============

		// clear window
		SDL_RenderClear(global::renderer);

		// background scrolling
		if (bg.rect.y > global::SCREEN_HEIGHT - 1) // reset bg positions
		{
			bg.rect.y = bg.initialY;
			bgRect.y = -bg.rect.h;
		}
		else // scroll bg's
		{
			bg.rect.y += bg.velocity;
			bgRect.y += bg.velocity;
		}

		// render bgs
		global::render(bg.currentTexture, &bg.rect);
		global::render(bg.currentTexture, &bgRect);

		// player alive routine (render player, enemy bullets)
		// ===================================================
		if (!playerIsDead)
		{
			playerDeathTimeout = SDL_GetTicks() + 500; // keep updating death timeout

			// get input
			getPlayerInput(player, keyState);

			// update hitbox position to middle of player
			hitbox.rect.x = (player.rect.x + player.rect.w / 2 - 4);
			hitbox.rect.y = (player.rect.y + player.rect.h / 2 - 4);

			// render player
			if (playerIsInvulnerable) // check invulnerability after respawn
				movement::blink(&player);
			else
			{
				global::render(player.currentTexture, &player.rect);
				global::render(hitbox.currentTexture, &hitbox.rect);
			}

			// render bullets
			// =========================
			renderBullets(currentPlayerBullets);
			renderBullets(currentEnemyBullets);

			// check for enemy bullet collision (hitbox is player middle)
			for (auto &bullet : currentEnemyBullets)
			{
				if (!playerIsInvulnerable && SDL_HasIntersection(&hitbox.rect, &bullet.rect))
				{
					playerIsDead = true;
					deaths++;
					break;
				}
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
		if(enemyWaves.size() > 0)	
		{
			if(enemyWaves.front().size() > 0)
				renderEnemies(enemyWaves.front(), currentPlayerBullets);
			else
				enemyWaves.erase(enemyWaves.begin());
		}

		// render current textures
		renderPresent:

		SDL_RenderPresent(global::renderer);

		SDL_Delay(16);
	}

	//==============
	// end game loop

	// close SDL subsystems
	global::close();
	DEBUG_MSG("** Gameplay stats **");
	DEBUG_MSG("Deaths: " << deaths);
	DEBUG_MSG("Graze: " << graze);

	return 0;
}
