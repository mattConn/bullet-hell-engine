#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#undef main

#include "global.h"
#include "gameObj.h"
#include "getInput.h"


int main(int argc, char* argv[])
{
	// init sdl
	if (!init(window, windowSurface))
	{
		printf("Init failed\n");
		return -1;
	}

	// hide cursor
	SDL_ShowCursor(SDL_DISABLE);


	// load textures
	allTextures[ENEMY] = loadTexture("enemy.png"),
	allTextures[ENEMY_BAT] = loadTexture("enemy-bat.png"),
	allTextures[PLAYER] = loadTexture("player.png"),
	allTextures[BULLET_RED] = loadTexture("bullet-red.png"),
	allTextures[BULLET_GREEN] = loadTexture("bullet-green.png"),
	allTextures[BULLET_ORANGE] = loadTexture("bullet-orange.png"),
	allTextures[CLOUD_BG] = loadTexture("cloud-bg.png"),
	allTextures[HITBOX] = loadTexture("hitbox.png");

	// base bullets
	gameObj* bulletRed = makeGameObj(BULLET_RED, 8, 33, 36);

	// init player
	gameObj* player = makeGameObj(PLAYER, 8, 50, 85);
	player->rect.x = SCREEN_WIDTH / 2 - 10 / 2;
	player->rect.y = SCREEN_HEIGHT / 2 - 100 / 2;
	player->duration = 200;

	// game states
	bool quit = false;
	bool paused = false;

	// event handler
	SDL_Event event;

	// realtime keystate
	const Uint8* keyState = SDL_GetKeyboardState(NULL);

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

		// get input
		getInput(player, keyState);

		// clear window
		SDL_RenderClear(renderer);

		render(allTextures[PLAYER], &player->rect);

		SDL_RenderPresent(renderer);

		SDL_Delay(16);
	} //end game loop



		// skip scene updating when paused
		//if (paused) goto renderPresent;

		// update scene
		// ============



/*

		// background scrolling
		if (bg.getRectY() > global::SCREEN_HEIGHT - 1) // reset bg positions
		{
			bg.setRectY(bg.getInitialY());
			bgRect.y = -bg.getRectH();
		}
		else // scroll bg's
		{
			bg.incRectY(bg.getVelocity());
			bgRect.y += bg.getVelocity();
		}

		// render bgs
		global::render(bg.getCurrentTexture(), bg.getRectPtr());
		global::render(bg.getCurrentTexture(), &bgRect);

		// player alive routine (render player, enemy bullets)
		// ===================================================
		if (!playerIsDead)
		{
			playerDeathTimeout = SDL_GetTicks() + 500; // keep updating death timeout

			// get input
			getPlayerInput(player, keyState);

			// update hitbox position to middle of player
			hitbox.setRectX(player.getRectX() + player.getRectW() / 2 - 4);
			hitbox.setRectY(player.getRectY() + player.getRectH() / 2 - 4);

			// render player
			if (playerIsInvulnerable) // check invulnerability after respawn
				animation::blink(&player);
			else
			{
				global::render(player.getCurrentTexture(), player.getRectPtr());
				global::render(hitbox.getCurrentTexture(), hitbox.getRectPtr());
			}

			// render bullets
			// =========================
			renderBullets(currentPlayerBullets);
			renderBullets(currentEnemyBullets);

			// check for enemy bullet collision (hitbox is player middle)
			for (auto &bullet : currentEnemyBullets)
			{
				if (!playerIsInvulnerable && SDL_HasIntersection(hitbox.getRectPtr(), bullet.getRectPtr()))
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

*/
	// close SDL subsystems
	closeSDL();

	return 0;
}
