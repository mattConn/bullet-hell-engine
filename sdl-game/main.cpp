#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#undef main

#include "debug_msg.h"
#include "functions.h"
#include "classes.h"

void foo();

int main(int argc, char *argv[])
{

	SDL_Texture *currentImage = nullptr;
	SDL_Texture *keypressImages[KEY_PRESS_TOTAL];

	// player
	playerObj player(1, 1, 100);
	std::cout << player.rect.w << std::endl;

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

	// list of all objects with collidable rectangles
	std::vector<SDL_Rect> collidableObj;

	// array of screen edges rectangles (1 px thick)
	SDL_Rect screenEdge[SCREEN_EDGE_TOTAL];
	screenEdge[SCREEN_EDGE_LEFT] = makeRect(0, 0, 1, SCREEN_HEIGHT);
	screenEdge[SCREEN_EDGE_RIGHT] = makeRect(SCREEN_WIDTH - 1, 0, 1, SCREEN_HEIGHT);
	screenEdge[SCREEN_EDGE_TOP] = makeRect(0, 0, SCREEN_WIDTH, 1);
	screenEdge[SCREEN_EDGE_BOTTOM] = makeRect(0, SCREEN_HEIGHT - 1, SCREEN_WIDTH, 1);

	// real-time state of key
	const Uint8 *keyState = SDL_GetKeyboardState(nullptr);

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

			if (SDL_HasIntersection(&player.rect, &screenEdge[SCREEN_EDGE_TOP]))
				player.rect.y = SCREEN_HEIGHT - player.rect.h;
			else
				player.rect.y -= 10;
		}
		else if (keyState[SDL_SCANCODE_DOWN])
		{
			currentImage = keypressImages[KEY_PRESS_DOWN];

			if (SDL_HasIntersection(&player.rect, &screenEdge[SCREEN_EDGE_BOTTOM]))
				player.rect.y = 0;
			else
				player.rect.y += 10;
		}
		else if (keyState[SDL_SCANCODE_LEFT])
		{
			currentImage = keypressImages[KEY_PRESS_LEFT];

			if (SDL_HasIntersection(&player.rect, &screenEdge[SCREEN_EDGE_LEFT]))
				player.rect.x = SCREEN_WIDTH - player.rect.w;
			else
				player.rect.x -= 10;
		}
		else if (keyState[SDL_SCANCODE_RIGHT])
		{
			currentImage = keypressImages[KEY_PRESS_RIGHT];

			if (SDL_HasIntersection(&player.rect, &screenEdge[SCREEN_EDGE_RIGHT]))
				player.rect.x = 0;
			else
				player.rect.x += 10;
		}
		else if (keyState[SDL_SCANCODE_RETURN]) // DEBUG: quick quitting
		{
			quit = true;
		}

		// update window
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, currentImage, nullptr, &player.rect);
		SDL_RenderPresent(renderer);

		SDL_Delay(16);
	}

	//==============
	// end game loop

	// close SDL subsystems
	close(windowSurface, window);

	return 0;
}
void foo()
{
	return;
}