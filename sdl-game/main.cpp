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

int main(int argc, char *argv[])
{

	SDL_Texture *currentImage = nullptr;

	SDL_Texture *keypressImages[KEY_PRESS_TOTAL];

	// init sdl
	if (!init(window, windowSurface))
	{
		DEBUG_MSG("Init failed");
		return -1;
	}

	// load all keyPress images
	keypressImages[KEY_PRESS_DEFAULT] = loadTexture("hello_world.bmp");
	keypressImages[KEY_PRESS_UP] = loadTexture("arrows_up.bmp");
	keypressImages[KEY_PRESS_DOWN] = loadTexture("arrows_down.bmp");
	keypressImages[KEY_PRESS_LEFT] = loadTexture("arrows_left.bmp");
	keypressImages[KEY_PRESS_RIGHT] = loadTexture("arrows_right.bmp");

	// TEST
	SDL_Rect rect = makeRect(1, 1, 100, 100);

	SDL_Rect wall[WALL_TOTAL];
	wall[WALL_LEFT] = makeRect(0, 0, 1, SCREEN_HEIGHT);
	wall[WALL_RIGHT] = makeRect(SCREEN_WIDTH - 1, 0, 1, SCREEN_HEIGHT);
	wall[WALL_TOP] = makeRect(0, 0, SCREEN_WIDTH, 1);
	wall[WALL_BOTTOM] = makeRect(0, SCREEN_HEIGHT - 1, SCREEN_WIDTH, 1);

	// real-time state of key
	const Uint8* keyState = SDL_GetKeyboardState(nullptr);

	// game loop
	//===========
	bool quit = false;
	SDL_Event event; // event handler

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
		if (keyState[SDL_SCANCODE_UP])
		{
			currentImage = keypressImages[KEY_PRESS_UP];

			if (SDL_HasIntersection(&rect, &wall[WALL_TOP]))
				rect.y = SCREEN_HEIGHT - rect.h;
			else
				rect.y -= 10;
		}
		else if (keyState[SDL_SCANCODE_DOWN])
		{
			currentImage = keypressImages[KEY_PRESS_DOWN];

			if (SDL_HasIntersection(&rect, &wall[WALL_BOTTOM]))
				rect.y = 0;
			else
				rect.y += 10;
		}
		else if (keyState[SDL_SCANCODE_LEFT])
		{
			currentImage = keypressImages[KEY_PRESS_LEFT];

			if (SDL_HasIntersection(&rect, &wall[WALL_LEFT]))
				rect.x = SCREEN_WIDTH - rect.w;
			else
				rect.x -= 10;
		}
		else if (keyState[SDL_SCANCODE_RIGHT])
		{
			currentImage = keypressImages[KEY_PRESS_RIGHT];

			if (SDL_HasIntersection(&rect, &wall[WALL_RIGHT]))
				rect.x = 0;
			else
				rect.x += 10;
		}
		else if (keyState[SDL_SCANCODE_RETURN]) // DEBUG: quick quitting
		{
			quit = true;
		}

		// update window
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, currentImage, nullptr, &rect); // use rect for x and y positioning
		SDL_RenderPresent(renderer);

		SDL_Delay(16);
	}

	//==============
	// end game loop

	// close SDL subsystems
	close(windowSurface, window);

	return 0;
}


