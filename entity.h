#include "global.h"

// base game entity
typedef struct Entity {
	int weight;
	bool collision;
	SDL_Texture *graphic;
	SDL_Rect rect;
	entityKind kind;
} entity;

// init platform entity
bool initPlatformEntity(entity *e, int x, int y, int w, int h, char *textureName);
