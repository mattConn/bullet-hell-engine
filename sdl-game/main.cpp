#include <iostream>
#include <vector>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#undef main

#include "debug.h"
#include "texture.h"
#include "global.h"
#include "gameObj.h"


int main(int argc, char *argv[])
{
    // init sdl
    if (!global::init(global::window, global::windowSurface))
    {
        DEBUG_MSG("Init failed");
        return -1;
    }

	// hide cursor
	SDL_ShowCursor(SDL_DISABLE);

	// load textures
	std::map<std::string, texture *> allTextures = {
		{"hello_world", new texture("hello_world.bmp")},
		{"arrows_up", new texture("arrows_up.bmp")},
	};

	// make player 
	// ===========

    // construct player
    gameObj *player = new gameObj(allTextures["arrows_up"]->getLoadedTexture(), 10, global::SCREEN_WIDTH/2 - 10/2, global::SCREEN_HEIGHT/2 - 100/2, 100, 100);
	// set player bullet properties
	player->setBullet(allTextures["hello_world"]->getLoadedTexture(), 25, 10, 10, 100);

    // list of all objects
    std::vector<gameObj*> currentObjs = {
    	new gameObj(allTextures["hello_world"]->getLoadedTexture(), 0, global::SCREEN_WIDTH - 100, 0, 10, 10)
	};

	// player bullet container
    std::vector<gameObj*> currentPlayerBullets;

    // game loop
    //===========
    while (!global::quit)
    {
        // event polling loop
        while (SDL_PollEvent(&global::event))
        {
            // window close event
            if (global::event.type == SDL_QUIT)
            {
                global::quit = true;
                break;
            }
        }

        // check keystate
        //===============
        if (global::keyState[SDL_SCANCODE_RETURN])
			global::quit = true;

		// toggle fullscreen F11
		if (global::keyState[SDL_SCANCODE_F11])
		{
			global::screenMode = global::screenMode == global::SCREEN_FULL ? global::SCREEN_WINDOWED : global::SCREEN_FULL;
			SDL_SetWindowFullscreen(global::window, global::screenMode);
		}

		// control player
		// ==============
		// slow down
		if (global::keyState[SDL_SCANCODE_LSHIFT])
			player->setVelocityMod(.35);
		else
			player->setVelocityMod(1);

		// fire
		if (global::keyState[SDL_SCANCODE_Z] && SDL_TICKS_PASSED(SDL_GetTicks(), player->getBullet()->getTimeout()))
		{
			currentPlayerBullets.push_back(player->getNewBullet());
			player->getBullet()->resetTimeout();
		}

		// move left
		if (global::keyState[SDL_SCANCODE_LEFT] && player->getRectL() > 0)
			player->incRectX(-player->getVelocity() * player->getVelocityMod());

		// move right
		if (global::keyState[SDL_SCANCODE_RIGHT] && player->getRectR() < global::SCREEN_WIDTH)
			player->incRectX(player->getVelocity() * player->getVelocityMod());

		// move up
		if (global::keyState[SDL_SCANCODE_UP] && player->getRectTop() > 0)
			player->incRectY(-player->getVelocity() * player->getVelocityMod());

		// move down
		if (global::keyState[SDL_SCANCODE_DOWN] && player->getRectBottom() < global::SCREEN_HEIGHT)
			player->incRectY(player->getVelocity() * player->getVelocityMod());

        // render scene
        // ============

        // update window
        SDL_RenderClear(global::renderer);

        // render player
        SDL_RenderCopy(global::renderer, player->getCurrentTexture(), nullptr, &player->getRect());

        // render all current objs
        // =======================
		for(auto obj : currentObjs)
            SDL_RenderCopy(global::renderer, obj->getCurrentTexture(), nullptr, &obj->getRect());

        // render all player bullets
        // =========================
		for(int i = 0; i < currentPlayerBullets.size(); i++)
		{
			currentPlayerBullets[i]->decRectY(currentPlayerBullets[i]->getVelocity());

			// remove bullet if offscreen
			if(currentPlayerBullets[i]->isOffscreen())
				currentPlayerBullets.erase(currentPlayerBullets.begin() + i);
			else
			//render bullet
				SDL_RenderCopy(global::renderer, currentPlayerBullets[i]->getCurrentTexture(), nullptr, &currentPlayerBullets[i]->getRect());
		}

        SDL_RenderPresent(global::renderer);

        SDL_Delay(16);
    }

    //==============
    // end game loop

    // close SDL subsystems
    global::close();

    return 0;
}
