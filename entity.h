#ifndef ENTITY_H
#define ENTITY_H

#include "global.h"

// base game entity
typedef struct Entity {
	int weight;
	bool collision;
	SDL_Texture *graphic;
	SDL_Rect rect;
	entityKind kind;
} entity;

// stack for storage of entities
typedef struct EntityStack {
	entity *arr;
	int top; // top item in stack
	int count; // current amt. in stack
} entityStack;

// init entity stack
bool initEntityStack(entityStack *es);

// push onto entity stack
bool pushEntityStack(entityStack *es, entity *e);

// init platform entity
bool initPlatformEntity(entity *e, int x, int y, int w, int h, char *textureName);

// init player entity
bool initPlayerEntity(entity *e, int weight, int x, int y, int w, int h, char *textureName);

bool updateEntityPhysics(entity *e);

#endif
