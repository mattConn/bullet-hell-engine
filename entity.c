#include "global.h"
#include "entity.h"

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
