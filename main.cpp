#include <iostream>

#include "include/SDL2/SDL.h"

using namespace std;

#include "functions.h"

int main()
{
    SDL_Window *window = nullptr;
    SDL_Surface *windowSurface = nullptr;
    SDL_Surface *currentImage = nullptr;

    SDL_Surface *keypressImages[KEY_PRESS_SURFACE_TOTAL];

    init(window, windowSurface);

    // load all keyPress images
    keypressImages[KEY_PRESS_SURFACE_DEFAULT] = loadImage("hello_world.bmp");
    keypressImages[KEY_PRESS_SURFACE_UP] = loadImage("arrows_up.bmp");
    keypressImages[KEY_PRESS_SURFACE_DOWN] = loadImage("arrows_down.bmp");
    keypressImages[KEY_PRESS_SURFACE_LEFT] = loadImage("arrows_left.bmp");
    keypressImages[KEY_PRESS_SURFACE_RIGHT] = loadImage("arrows_right.bmp");

    // event loop
    //===========
    bool quit = false;
    SDL_Event event;

    while (!quit)
    {
        // event polling loop
        //===================
        while (SDL_PollEvent(&event))
        {
            // window close event
            if (event.type == SDL_QUIT)
            {
                quit = true;
                break;
            }

            // keypress event
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                // up, down, left and right key presses
                //=====================================

                case SDLK_UP:
                    currentImage = keypressImages[KEY_PRESS_SURFACE_UP];
                    break;

                case SDLK_DOWN:
                    currentImage = keypressImages[KEY_PRESS_SURFACE_DOWN];
                    break;

                case SDLK_LEFT:
                    currentImage = keypressImages[KEY_PRESS_SURFACE_LEFT];
                    break;

                case SDLK_RIGHT:
                    currentImage = keypressImages[KEY_PRESS_SURFACE_RIGHT];
                    break;

                default:
                    currentImage = keypressImages[KEY_PRESS_SURFACE_DEFAULT];
                }
            }
        }
        //=======================
        // end event polling loop

        // update window
        SDL_BlitSurface(currentImage, nullptr, windowSurface, nullptr);
        SDL_UpdateWindowSurface(window);

        SDL_Delay(16);
    }
    //===============
    // end event loop


    close(windowSurface, window);

    return 0;
}


