#include <iostream>

#include "include/SDL2/SDL.h"

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init(SDL_Window *&window, SDL_Surface *&surface);
bool loadMedia();
bool close();

int main()
{
    SDL_Window *window = nullptr;
    SDL_Surface *surface = nullptr;
    SDL_Surface *image = nullptr;

    init(window, surface);

    SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format,0xFF, 0xFF,0xFF) );
    SDL_UpdateWindowSurface(window);
    SDL_Delay(2E3);

    // A basic main loop to prevent blocking
    // =====================================
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
    // =====================================
    // end event loop

    SDL_DestroyWindow(window);
    SDL_Quit();

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
