#include "global.h"
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

SDL_Window *window = NULL; // main window
SDL_Surface *windowSurface = NULL; // surface for main window
SDL_Renderer *renderer = NULL; // main renderer


// functions
// =========

// SDL rect wrapper
SDL_Rect makeRect(const int *xPos, const int *yPos, const int *width, const int *height)
{
	SDL_Rect rect;
	rect.x = *xPos;

	rect.y = *yPos;
	rect.w = *width;
	rect.h = *height;

	return rect;
}

bool render(const char* texture, const SDL_Rect *rect)
{
	if (SDL_RenderCopy(renderer, loadTexture(texture), NULL, rect) == 0)
		return true;
	else
		return false;
}

bool init(SDL_Window *window, SDL_Surface *windowSurface)
{
	printf("** Begin init **\n");

	// init video
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not init video: %s\n", SDL_GetError());
		return false;
	}
	printf("Init video");

	// init PNG loading
	if (!IMG_Init(IMG_INIT_PNG))
	{
		printf("Could not init PNG loading: %s\n", SDL_GetError());
		return false;
	}
	printf("Init PNG loading\n");

	// create window
	window = SDL_CreateWindow("Bullet Hell",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		printf("SDL window creation error: %s\n", SDL_GetError());
		return false;
	}
	printf("Created window: w: %d h: %d\n", SCREEN_WIDTH, SCREEN_HEIGHT );

	// init renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == NULL)
	{
		printf("Could not init renderer: %s\n", SDL_GetError());
		return false;
	}
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
	printf("Init renderer\n");

	// assign window surface
	windowSurface = SDL_GetWindowSurface(window);

	printf("** End init **\n");

	return true;
}

SDL_Surface *loadImage(const char fileName[])
{
	// load image
	SDL_Surface *imageSurface = IMG_Load(fileName);
	SDL_Surface *optimizedSurface = NULL;

	if (imageSurface == NULL)
	{
		printf("Unable to load image %s: %s\n", fileName, SDL_GetError());
		return NULL;
	}

	// optimize image
	optimizedSurface = SDL_ConvertSurface(imageSurface, windowSurface->format, 0);
	if (optimizedSurface == NULL)
	{
		printf("Unable to optimize surface %s: %s\n", fileName, SDL_GetError());
		return NULL;
	}

	// free unoptimized surface
	SDL_FreeSurface(imageSurface);

	printf("Load image successful: %s\n", fileName);

	return optimizedSurface;
}

// IMG_LoadTexture wrapper
SDL_Texture *loadTexture(const char fileName[])
{
	SDL_Texture *texture = IMG_LoadTexture(renderer, fileName);

	if (texture == NULL)
	{
		printf("Unable to load texture %s: %s\n", fileName, SDL_GetError());
		return NULL;
	}

	printf("Load texture successful: %s\n");

	return texture;
}

bool close()
{
	//Deallocate windowSurface
	SDL_FreeSurface(windowSurface);
	windowSurface = NULL;

	//Destroy window
	SDL_DestroyWindow(window);
	window = NULL;

	// Destroy renderer
	SDL_DestroyRenderer(renderer);

/*
	// Destroy textures
	for (auto &texture : allTextures)
		SDL_DestroyTexture(texture.second);

	// Destroy base bullets 
	for (auto &bullet : baseBullets)
		delete bullet.second;

	// Destroy base enemies
	for (auto &enemy : baseEnemies)
		delete enemy.second;
*/

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();

	printf("Close successful\n");
	return true;
}

int main(){return 0;}
