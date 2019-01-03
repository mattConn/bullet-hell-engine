#include "include/SDL2/SDL.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

bool init(SDL_Window *&window, SDL_Surface *&windowSurface);
SDL_Surface *loadImage(char fileName[]);
bool close(SDL_Surface *&surface, SDL_Window *&window);

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

SDL_Surface *loadImage(char fileName[])
{
    SDL_Surface *imageSurface = SDL_LoadBMP(fileName);

    if(imageSurface == nullptr)
    {
        cout << "Unable to load image" << fileName << ": " << SDL_GetError() << endl;
        return imageSurface;
    }

    return imageSurface;
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
