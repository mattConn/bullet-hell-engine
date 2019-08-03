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
		i->setAnimation(animation::downAndLeft);
		i->setBullet("player-bullet", 10, 20, 20, 100);
	}


	// make player 
	// ===========

	// construct player
	gameObj player = gameObj("player", 10, global::SCREEN_WIDTH / 2 - 10 / 2, global::SCREEN_HEIGHT / 2 - 100 / 2, 50, 85);

	// set player bullet properties
	player.setBullet("player-bullet", 10, 20, 20, 100);

	// game state booleans
	bool quit = false;
	bool paused = false;

	// event handler
	SDL_Event event;

	// realtime keystate
	const Uint8* keyState = SDL_GetKeyboardState(nullptr);

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
				//case SDLK_F11: // fullscreen
				//	global::screenMode = global::screenMode == global::SCREEN_FULL ? global::SCREEN_WINDOWED : global::SCREEN_FULL;
				//	SDL_SetWindowFullscreen(global::window, global::screenMode);
				//	break;
				case SDLK_RETURN: // quit
					quit = true;
					break;
				}
			} // end get keyboard events
		} // end poll events


		// run when not paused
		if (!paused)
		{
			// get input
			getPlayerInput(player, keyState);

			// render scene
			// ============

			// update window
			SDL_RenderClear(global::renderer);

			// render player
			SDL_RenderCopy(global::renderer, global::allTextures[player.getCurrentTexture()], nullptr, player.getRectPtr());

			// render enemies
			renderEnemies(currentEnemies, currentPlayerBullets);

			// render all player bullets
			// =========================
			for (int i = 0; i < currentPlayerBullets.size(); i++)
			{
				// translate up
				currentPlayerBullets[i].decRectY(currentPlayerBullets[i].getVelocity());

				// remove bullet if offscreen
				if (currentPlayerBullets[i].isOffscreen())
					currentPlayerBullets.erase(currentPlayerBullets.begin() + i);
				else
					//render bullet
					SDL_RenderCopy(global::renderer, global::allTextures[currentPlayerBullets[i].getCurrentTexture()], nullptr, currentPlayerBullets[i].getRectPtr());
			}

			// render all enemy bullets
			// ========================
			for (int i = 0; i < currentEnemyBullets.size(); i++)
			{
				// translate up
				currentEnemyBullets[i].incRectY(currentEnemyBullets[i].getVelocity());

				if (currentEnemyBullets[i].isOffscreen())
					currentEnemyBullets.erase(currentEnemyBullets.begin() + i);
				else
					SDL_RenderCopy(global::renderer, global::allTextures[currentEnemyBullets[i].getCurrentTexture()], nullptr, currentEnemyBullets[i].getRectPtr());
			}

		} // end if not paused block

		SDL_RenderPresent(global::renderer);

		SDL_Delay(16);
	}

	//==============
	// end game loop

	// close SDL subsystems
	global::close();

	return 0;
}
