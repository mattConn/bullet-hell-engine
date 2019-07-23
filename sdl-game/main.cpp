#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//#include <Box2D/Box2D.h>
#undef main

#include "debug.h"
#include "global.h"
#include "gameObj.h"
#include "playerObj.h"


int main(int argc, char *argv[])
{
    // init sdl
    if (!g::init(g::window, g::windowSurface))
    {
        DEBUG_MSG("Init failed");
        return -1;
    }

	// hide cursor
	SDL_ShowCursor(SDL_DISABLE);

    // construct player
    playerObj *player = new playerObj(g::SCREEN_WIDTH/2 - 10/2, g::SCREEN_HEIGHT/2 - 100/2, 10, 100);

    // list of all objects
    std::vector<gameObj*> currentObjs;

    // right wall
    gameObj *wall = new gameObj("hello_world.bmp", true, g::OBJ_BLOCK, g::SCREEN_WIDTH - 100, 0, 100, g::SCREEN_HEIGHT);
    gameObj *wall2 = new gameObj("hello_world.bmp", true, g::OBJ_BLOCK, 0, 0, 100, g::SCREEN_HEIGHT);
    gameObj *block = new gameObj("hello_world.bmp", true, g::OBJ_BLOCK, g::SCREEN_WIDTH/4, g::SCREEN_HEIGHT/4, 300, 100);
    //gameObj *block2 = new gameObj("hello_world.bmp", true, g::OBJ_BLOCK, 0, g::SCREEN_HEIGHT - 100, g::SCREEN_WIDTH, 100);

    currentObjs.push_back(wall);
    currentObjs.push_back(wall2);
    currentObjs.push_back(block);
    //currentObjs.push_back(block2);

    // game loop
    //===========
    while (!g::quit)
    {
        // event polling loop
        while (SDL_PollEvent(&g::event))
        {
            // window close event
            if (g::event.type == SDL_QUIT)
            {
                g::quit = true;
                break;
            }
        }

        // check keystate
        //===============
        #ifdef DEBUG
        if (g::keyState[SDL_SCANCODE_RETURN]) // DEBUG: quick quitting
            g::quit = true;
        #endif

		// toggle fullscreen F11
		if (g::keyState[SDL_SCANCODE_F11])
		{
			g::screenMode = g::screenMode == g::SCREEN_FULL ? g::SCREEN_WINDOWED : g::SCREEN_FULL;
			SDL_SetWindowFullscreen(g::window, g::screenMode);
		}

		// check collision, keystate, update physics
		player->updatePlayer(currentObjs);

        // render scene
        // ============

        // update window
        SDL_RenderClear(g::renderer);

        // render player
        SDL_RenderCopy(g::renderer, player->getCurrentTexture(), nullptr, &player->rect);

        // render all current objs
        for(auto obj : currentObjs)
            SDL_RenderCopy(g::renderer, obj->getCurrentTexture(), nullptr, &obj->rect);

        SDL_RenderPresent(g::renderer);

        SDL_Delay(16);
    }

    //==============
    // end game loop

    // close SDL subsystems
    g::close();

    return 0;
}
