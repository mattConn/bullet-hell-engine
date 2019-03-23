#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//#undef main

#include "global.h"
#include "entity.h"

int main(int argc, char *argv[])
{
	// all entities present in game
	entityStack allEntities;
	initEntityStack(&allEntities);

	// all entities with collision
	entityStack collisionEntities;
	initEntityStack(&collisionEntities);


	// name to display in window
	windowName = "new SDL game";

	// set screen dimensions
	SCREEN_WIDTH = 800;
	SCREEN_HEIGHT = 600;

	// error file and output file
	errFile = stderr;
	outFile = stdout;

    // init sdl
    if (!init(window, windowSurface))
    {
		writeErr("Init failed.", NULL);
        return 1;
    }

    //  walls
	entity rwall, lwall, floor;
	initPlatformEntity(&rwall, SCREEN_WIDTH - 100, 0, 100, SCREEN_HEIGHT, "hello_world.bmp");
	initPlatformEntity(&lwall, 0, 0, 100, SCREEN_HEIGHT, "hello_world.bmp");
	initPlatformEntity(&floor, 0, SCREEN_HEIGHT - 100, SCREEN_WIDTH, 100, "hello_world.bmp");

	// store in allEntities stack
	pushEntityStack(&allEntities, &lwall);
	pushEntityStack(&allEntities, &rwall);
	pushEntityStack(&allEntities, &floor);

	entity block;
	initPlatformEntity(&block, 200, 50, 100, 100, "hello_world.bmp");
	block.weight = 1;
	pushEntityStack(&allEntities, &block);

	// store all entities with collision enabled
	for(int i=0; i < allEntities.count; i++)
	{
		if(allEntities.arr[i].collision)
			pushEntityStack(&collisionEntities, &allEntities.arr[i]);
	}

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

        // render all current objs
		for(int i = 0; i < allEntities.count; i++)
		{
			for(int j = 0; j < allEntities.count; j++)
			{
				if(j != i) // don't check for collision with self
				{
					// check for collision on all entities
					setEntityCollision(&allEntities.arr[i], &allEntities.arr[j]);
				}
			}

			// update entities physics
			updateEntityPhysics(&allEntities.arr[i]);

			// render entities
        	SDL_RenderCopy(renderer, allEntities.arr[i].graphic, NULL, &allEntities.arr[i].rect);
		}

        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    //==============
    // end game loop

    // close SDL subsystems
    closeSDLSubsystems();

	// free entity stacks
	free(allEntities.arr);
	free(collisionEntities.arr);

    return 0;
}
