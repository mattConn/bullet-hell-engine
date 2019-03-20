#include "global.h"
#include "entity.h"

bool initEntityStack(entityStack *es)
{
	es->top = -1;
	es->count = 0;
	es->arr = NULL;
}

bool pushEntityStack(entityStack *es, entity *e)
{
	es->top++;
	es->count++;
	
	// if first item
	if(!es->arr)
		es->arr = (entity*) malloc(sizeof(entity));
	else
		es->arr = (entity*) realloc(es->arr, es->count * sizeof(entity));

	es->arr[es->top] = *e;
}

bool initPlatformEntity(entity *e, int x, int y, int w, int h, char *textureName)
{
	e->weight = 0;
	e->collision = true;
	e->graphic = loadTexture(textureName);
	e->rect = makeRect(x,y,w,h);
	e->kind = PLATFORM;

	writeMsg("Successful init platform.");
}

bool initPlayerEntity(entity *e, int weight, int x, int y, int w, int h, char *textureName)
{
	e->weight = weight;
	e->collision = true;
	e->graphic = loadTexture(textureName);
	e->rect = makeRect(x,y,w,h);
	e->kind = PLAYER;
}

bool updateEntityPhysics(entity *e)
{
	if(e->weight > 0)
		e->rect.y += gravity * e->weight;
}
