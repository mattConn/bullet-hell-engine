#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#undef main


// debug message macro
#define DEBUG true
#if DEBUG
#define DEBUG_MSG(str) do { std::cout << str << std::endl; } while( false )
#else
#define DEBUG_MSG(str) do { } while ( false )
#endif


#include "functions.h"

int main()
{

	SDL_Texture *currentImage = nullptr;

	SDL_Texture *keypressImages[KEY_PRESS_TOTAL];

	// init sdl
	init(window, windowSurface);

	// load all keyPress images
	keypressImages[KEY_PRESS_DEFAULT] = loadTexture("hello_world.bmp");
	keypressImages[KEY_PRESS_UP] = loadTexture("arrows_up.bmp");
	keypressImages[KEY_PRESS_DOWN] = loadTexture("arrows_down.bmp");
	keypressImages[KEY_PRESS_LEFT] = loadTexture("arrows_left.bmp");
	keypressImages[KEY_PRESS_RIGHT] = loadTexture("arrows_right.bmp");
	

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

				case SDLK_UP:
					currentImage = keypressImages[KEY_PRESS_UP];
					break;

				case SDLK_DOWN:
					currentImage = keypressImages[KEY_PRESS_DOWN];
					break;

				case SDLK_LEFT:
					currentImage = keypressImages[KEY_PRESS_LEFT];
					break;


				case SDLK_RIGHT:
					currentImage = keypressImages[KEY_PRESS_RIGHT];
					break;

				// DEBUG: Easy quitting
				case SDLK_RETURN:
					quit = true;
					break;

				default:
					currentImage = keypressImages[KEY_PRESS_DEFAULT];
				}
			}
		}
		//=======================
		// end event polling loop

		// update window
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, currentImage, nullptr, nullptr); // use rect for x and y positioning
		SDL_RenderPresent(renderer);

		SDL_Delay(16);
	}
	//===============
	// end event loop

	close(windowSurface, window);

	return 0;
}


