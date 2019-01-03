#include <iostream>

#include "include/SDL2/SDL.h"

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init(SDL_Window *&window, SDL_Surface *&windowSurface);
bool loadMedia(SDL_Surface *&imageSurface, char fileName[]);
bool close(SDL_Surface *&surface, SDL_Window *&window);

enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

int main()
{
    SDL_Window *window = nullptr;
    SDL_Surface *windowSurface = nullptr;
    SDL_Surface *currentImage = nullptr;

    SDL_Surface *keypressImages[KEY_PRESS_SURFACE_TOTAL];
    cout << "KEY_PRESS_SURFACE_TOTAL: " << KEY_PRESS_SURFACE_TOTAL << endl;

    init(window, windowSurface);

    loadMedia(currentImage, "hello_world.bmp");

    // load all keyPress images
    loadMedia(keypressImages[KEY_PRESS_SURFACE_DEFAULT], "hello_world.bmp");
    loadMedia(keypressImages[KEY_PRESS_SURFACE_UP], "arrows_up.bmp");
    loadMedia(keypressImages[KEY_PRESS_SURFACE_DOWN], "arrows_down.bmp");
    loadMedia(keypressImages[KEY_PRESS_SURFACE_LEFT], "arrows_left.bmp");
    loadMedia(keypressImages[KEY_PRESS_SURFACE_RIGHT], "arrows_right.bmp");

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

bool init(SDL_Window *&window, SDL_Surface *&windowSurface)
{
    if( SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "SDL could not init: " << SDL_GetError() << endl;
        return false;
    }

    window = SDL_CreateWindow("SDL Tutorial",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH,
                              SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);

    if(window == nullptr)
    {
        cout << "SDL window creation error: " << SDL_GetError() << endl;
        return false;
    }

    windowSurface = SDL_GetWindowSurface(window);

    return true;
}

bool loadMedia(SDL_Surface *&imageSurface, char fileName[])
{
    imageSurface = SDL_LoadBMP(fileName);

    if(imageSurface == nullptr)
    {
        cout << "Unable to load image: " << SDL_GetError() << endl;
        return false;
    }

    return true;
}

bool close(SDL_Surface *&surface, SDL_Window *&window)
{
    //Deallocate surface
    SDL_FreeSurface( surface );
    surface = nullptr;

    //Destroy window
    SDL_DestroyWindow( window );
    window = nullptr;

    //Quit SDL subsystems
    SDL_Quit();

    return true;
}
