#include <iostream>

#include "include/SDL2/SDL.h"

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init(SDL_Window *&window, SDL_Surface *&surface);
bool loadMedia(SDL_Surface *&image, char fileName[]);
bool close(SDL_Surface *&surface, SDL_Window *&window);
void eventLoop();

int main()
{
    SDL_Window *window = nullptr;
    SDL_Surface *surface = nullptr;
    SDL_Surface *image = nullptr;

    init(window, surface);
    loadMedia(image, "hello_world.bmp");

    SDL_BlitSurface(image, nullptr, surface, nullptr);
    SDL_UpdateWindowSurface(window);

    eventLoop();

    close(surface, window);

    return 0;
}

bool init(SDL_Window *&window, SDL_Surface *&surface)
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
    else
        surface = SDL_GetWindowSurface(window);

    return true;
}

bool loadMedia(SDL_Surface *&image, char fileName[])
{
    image = SDL_LoadBMP(fileName);

    if(image == nullptr)
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


void eventLoop()
{
    bool is_running = true;
    SDL_Event event;

    while (is_running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                is_running = false;
            }
        }
        SDL_Delay(16);
    }

}
