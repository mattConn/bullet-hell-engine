#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
//#include <Box2D/Box2D.h>
#undef main

#include "debug.h"
#include "global.h"
#include "gameObj.h"
#include "playerObj.h"


int main(int argc, char *argv[])
{
    game_beginning: // label for debug game restart

    // init sdl
    if (!g::init(g::window, g::windowSurface))
    {
        DEBUG_MSG("Init failed");
        return -1;
    }

    // construct player
    playerObj *player = new playerObj(1, 1, 10, 100);

    // list of all objects
    std::vector<gameObj*> currentObjs;

    // right wall
    gameObj *wall = new gameObj("hello_world.bmp", true, g::OBJ_BLOCK, g::SCREEN_WIDTH - 100, 0, 100, g::SCREEN_HEIGHT);
    gameObj *block = new gameObj("hello_world.bmp", true, g::OBJ_BLOCK, g::SCREEN_WIDTH/4, g::SCREEN_HEIGHT/4, 300, 100);
    gameObj *block2 = new gameObj("hello_world.bmp", true, g::OBJ_BLOCK, 0, g::SCREEN_HEIGHT - 100, g::SCREEN_WIDTH, 100);

    currentObjs.push_back(wall);
    currentObjs.push_back(block);
    currentObjs.push_back(block2);

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

        if (g::keyState[SDL_SCANCODE_R]) // DEBUG: restart
        {
            DEBUG_MSG("\n** restart **\n");
            goto restart_label;
        }
        #endif

        player->checkCollision(currentObjs); // check collision against current objs

        player->checkKeyState(); // check keys, update flags
        player->updatePhysics(); // update player physics

        // render scene
        // ============
		
        // update window
        SDL_SetRenderDrawColor(g::renderer, 0,0,0,0);
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

    #ifdef DEBUG
    restart_label:
    goto game_beginning;
    #endif // DEBUG: game restarting

}
