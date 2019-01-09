#pragma once
#include <SDL.h>
#include <vector>

namespace g {
	extern bool quit;

	// screen dimensions
	extern const int SCREEN_HEIGHT;
	extern const int SCREEN_WIDTH;

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
	enum gameObjType
	{
		OBJ_PLATFORM,
		OBJ_WALL,
		OBJ_PLAYER,
		OBJ_ENEMY,
		OBJ_GRAPHIC,
		OBJ_NO_COLLISION,
		OBJ_TOTAL
	};

	// array of screen edges rectangles (1 px thick)
	extern SDL_Rect screenEdge[];

	extern SDL_Window *window; // main window
	extern SDL_Surface *windowSurface; // surface for main window
	extern SDL_Renderer *renderer; // main renderer

	// real-time state of key
	extern const Uint8 *keyState;

	// event handler
	extern SDL_Event event;

	// function prototypes
	// ===================

	// SDL rect wrapper
	extern SDL_Rect makeRect(const int &x, const int &y, const int &w, const int &h = -1);

	// init SDL subsystems, windows etc.
	extern bool init(SDL_Window *&window, SDL_Surface *&windowSurface);

	// load image and optimize
	extern SDL_Surface *loadImage(char fileName[]);

	// SDL image wrapper
	extern SDL_Texture *loadTexture(const char filename[]);

	// free memory and quit SDL subsytems
	extern bool close();

} // end namespace