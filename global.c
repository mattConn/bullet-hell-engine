#include "global.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

bool quit = false;

int SCREEN_WIDTH = 0;
int SCREEN_HEIGHT = 0;

int gravity = 1;

// error function
#ifdef DEBUG
void writeErr(const char *err, char *more)
{
	fprintf(errFile, "** ERROR: %s\n\t%s\n\t%s\n", err, SDL_GetError(), more);
}

void writeMsg(const char *err)
{
	fprintf(outFile, "%s\n", err);
}
#else
void writeErr(const char *err, char *more)
{
	// Do nothing
}

void writeMsg(const char *err)
{
	// Do nothing
}
#endif


// left, right, top, bottom screen edge
SDL_Rect screenEdge[SCREEN_EDGE_TOTAL];

SDL_Window *window = NULL; // main window
SDL_Surface *windowSurface = NULL; // surface for main window
SDL_Renderer *renderer = NULL; // main renderer


// functions
// =========

// SDL rect wrapper
SDL_Rect makeRect(int x, int y, int w, int h)
{
	SDL_Rect rect;
	rect.x = x;

	rect.y = y;
	rect.w = w;
	rect.h = h;

	return rect;
}

bool init(SDL_Window *window, SDL_Surface *windowSurface)
{
	// define screen edges
	screenEdge[SCREEN_EDGE_LEFT] = makeRect(0, 0, 1, SCREEN_HEIGHT);
	screenEdge[SCREEN_EDGE_RIGHT] = makeRect(SCREEN_WIDTH - 1, 0, 1, SCREEN_HEIGHT);
	screenEdge[SCREEN_EDGE_TOP] = makeRect(0, 0, SCREEN_WIDTH, 1);
	screenEdge[SCREEN_EDGE_BOTTOM] = makeRect(0, SCREEN_HEIGHT - 1, SCREEN_WIDTH, 1);

	// keystate
	keyState = SDL_GetKeyboardState(NULL);

	writeMsg("** Begin init **");

	// init video
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		writeErr("SDL could not init video.", NULL);
		return false;
	}
	writeMsg("Init video");

	// init PNG loading
	if (!IMG_Init(IMG_INIT_PNG))
	{
		writeErr("Could not init PNG loading.", NULL);
		return false;
	}
	writeMsg("Init PNG loading");

	// create window
	window = SDL_CreateWindow(windowName,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		writeErr("SDL window creation error.", NULL);
		return false;
	}
	writeMsg("Created window");

	// init renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == NULL)
	{
		writeErr("Could not init renderer.", NULL);
		return false;
	}
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
	writeMsg("Init renderer");

	// assign window surface
	windowSurface = SDL_GetWindowSurface(window);

	writeMsg("** End init **");

	return true;
}

SDL_Surface *loadImage(const char *fileName)
{
	// load image
	SDL_Surface *imageSurface = IMG_Load(fileName);
	SDL_Surface *optimizedSurface = NULL;

	if (imageSurface == NULL)
	{
		writeErr("Unable to load image: ", fileName);
		return NULL;
	}

	// optimize image
	optimizedSurface = SDL_ConvertSurface(imageSurface, windowSurface->format, 0);
	if (optimizedSurface == NULL)
	{
		writeErr("Unable to optimize surface: ", fileName);
		return NULL;
	}

	// free unoptimized surface
	SDL_FreeSurface(imageSurface);

	writeMsg("Load image successful.");

	return optimizedSurface;
}

// IMG_LoadTexture wrapper
SDL_Texture *loadTexture(char *fileName)
{
	SDL_Texture *texture = IMG_LoadTexture(renderer, fileName);

	if (texture == NULL)
	{
		writeErr("Unable to load texture: ", fileName);
		return NULL;
	}

	writeMsg("Load texture successful.");

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

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();

	writeMsg("Close successful.");
	return true;
}
