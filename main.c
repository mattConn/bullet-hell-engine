#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//#undef main

#include "global.h"

int main(int argc, char *argv[])
{
	// name to display in window
	windowName = "new SDL game";

	// error file and output file
	errFile = stderr;
	outFile = stdout;

    // init sdl
    if (!init(window, windowSurface))
    {
		writeErr("Init failed.", NULL);
        return 1;
    }

/*
    // construct player
    playerObj *player = new playerObj(200, 1, 10, 100);

    // list of all objects
    std::vector<gameObj*> currentObjs;

    // right wall
    gameObj *wall = new gameObj("hello_world.bmp", true, OBJ_BLOCK, SCREEN_WIDTH - 100, 0, 100, SCREEN_HEIGHT);
    gameObj *wall2 = new gameObj("hello_world.bmp", true, OBJ_BLOCK, 0, 0, 100, SCREEN_HEIGHT);
    gameObj *block = new gameObj("hello_world.bmp", true, OBJ_BLOCK, SCREEN_WIDTH/4, SCREEN_HEIGHT/4, 300, 100);
    gameObj *block2 = new gameObj("hello_world.bmp", true, OBJ_BLOCK, 0, SCREEN_HEIGHT - 100, SCREEN_WIDTH, 100);

    currentObjs.push_back(wall);
    currentObjs.push_back(wall2);
    currentObjs.push_back(block);
    currentObjs.push_back(block2);

*/

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
        }

        // check keystate
        //===============
        #ifdef DEBUG
        if (keyState[SDL_SCANCODE_RETURN]) // DEBUG: quick quitting
            quit = true;
        #endif

		/*
        player->checkCollision(currentObjs); // check collision against current objs

        player->checkKeyState(); // check keys, update flags
        player->updatePhysics(); // update player physics
		*/

        // render scene
        // ============

        // update window
        SDL_RenderClear(renderer);

        // render player
        // SDL_RenderCopy(renderer, player->getCurrentTexture(), nullptr, &player->rect);

        // render all current objs
		/*
        for(auto obj : currentObjs)
            SDL_RenderCopy(renderer, obj->getCurrentTexture(), nullptr, &obj->rect);
		*/

        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    //==============
    // end game loop

    // close SDL subsystems
    close();

    return 0;
}
