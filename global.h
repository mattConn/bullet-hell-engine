#ifndef GLOBAL_H
#define GLOBAL_H

#include <SDL2/SDL.h>
#include <stdio.h>

typedef enum Bool { false, true } bool;

bool quit;

// name to display in window
const char *windowName;

// error file and output file
FILE *errFile;
FILE *outFile;

// error function
void writeErr(const char *err, char *more);

// print function
void writeMsg(const char *err);

// screen dimensions
const int SCREEN_HEIGHT;
const int SCREEN_WIDTH;

// wall position enum
enum screenEdgePos
{
	SCREEN_EDGE_LEFT,
	SCREEN_EDGE_RIGHT,
	SCREEN_EDGE_TOP,
	SCREEN_EDGE_BOTTOM,
	SCREEN_EDGE_TOTAL
};

// obj types
enum entityKind
{
	PLATFORM,
	PLAYER,
	ENEMY,
	GRAPHIC,
	TOTAL_KINDS
};

// array of screen edges rectangles (1 px thick)
SDL_Rect screenEdge[];

SDL_Window *window; // main window
SDL_Surface *windowSurface; // surface for main window
SDL_Renderer *renderer; // main renderer

// real-time state of key
const Uint8 *keyState;

// event handler
SDL_Event event;

// function prototypes
// ===================

// SDL rect wrapper
SDL_Rect makeRect(int x, int y, int w, int h);

// init SDL subsystems, windows etc.
bool init(SDL_Window *window, SDL_Surface *windowSurface);

// load image and optimize
SDL_Surface *loadImage(const char *fileName);

// SDL image wrapper
SDL_Texture *loadTexture(char *filename);

// free memory and quit SDL subsytems
bool close();

#endif
