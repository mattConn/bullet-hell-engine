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
	global::allTextures["hello_world"] = global::loadTexture("hello_world.bmp");
	global::allTextures["arrows_up"] = global::loadTexture("arrows_up.bmp");
	global::allTextures["player"] = global::loadTexture("player.png");
	global::allTextures["player-bullet"] = global::loadTexture("player-bullet.png");

	// list of all objects
	std::vector<gameObj> currentObjs = {
		gameObj("hello_world", 10, 500, 10, 50, 50),
		gameObj("hello_world", 10, 600, 50, 50, 50),
		gameObj("hello_world", 10, 400, 20, 50, 50),
	};

	currentObjs[0].setAnimation(animation::downAndLeft);
	currentObjs[1].setAnimation(animation::downAndLeft);
	currentObjs[2].setAnimation(animation::downAndLeft);


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

			// render scene
			// ============

			// update window
			SDL_RenderClear(global::renderer);

			// render player
			SDL_RenderCopy(global::renderer, global::allTextures[player.getCurrentTexture()], nullptr, player.getRectPtr());

			// render all current objs
			// =======================
			for (int i = 0; i < currentObjs.size(); i++)
			{
				if (currentObjs[i].playAnimation()) // if playing animation
				{
					// render
					SDL_RenderCopy(global::renderer, global::allTextures[currentObjs[i].getCurrentTexture()], nullptr, currentObjs[i].getRectPtr());

					// check for player bullet collision
					for (int j = 0; j < currentPlayerBullets.size(); j++)
					{
						if (SDL_HasIntersection(currentObjs[i].getRectPtr(), currentPlayerBullets[j].getRectPtr()))
						{
							currentObjs.erase(currentObjs.begin() + i);
							currentPlayerBullets.erase(currentPlayerBullets.begin() + j);
							break; // avoid out of range index
						}
					}
				}
				else // no animation, offscreen: remove
					currentObjs.erase(currentObjs.begin() + i);
			}

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
