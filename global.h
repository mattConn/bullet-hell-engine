#pragma once
#include <stdbool.h>
#include <SDL2/SDL.h>

// screen dimensions
extern const int SCREEN_HEIGHT;
extern const int SCREEN_WIDTH;

// keypress enum for relating textures to keypress events
enum KeyPresses
{
	KEY_PRESS_DEFAULT,
	KEY_PRESS_UP,
	KEY_PRESS_DOWN,
	KEY_PRESS_LEFT,
	KEY_PRESS_RIGHT,
	KEY_PRESS_TOTAL
};

typedef enum Textures {
	ENEMY,
	ENEMY_BAT,
	PLAYER,
	BULLET_RED,
	BULLET_GREEN,
	BULLET_ORANGE,
	CLOUD_BG,
	HITBOX,
	MAX_TEXTURES
} textures;

extern SDL_Texture* allTextures[];

extern SDL_Window *window; // main window
extern SDL_Surface *windowSurface; // surface for main window
extern SDL_Renderer *renderer; // main renderer


// function prototypes
// ===================

// SDL rect wrapper
extern SDL_Rect makeRect(const int x, const int y, const int w, const int h);

// SDL_RenderCopy wrapper
extern bool render(SDL_Texture* texture, const SDL_Rect* rect);

// init SDL subsystems, windows etc.
extern bool init(SDL_Window *window, SDL_Surface *windowSurface);

// load image and optimize
extern SDL_Surface *loadImage(const char fileName[]);

// SDL image wrapper
extern SDL_Texture *loadTexture(const char filename[]);

// free memory and quit SDL subsytems
extern bool closeSDL();
