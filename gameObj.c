#include <stdbool.h>
#include "global.h"
#include "gameObj.h"

bool isOffscreen(gameObj* obj)
{
	if (obj->rect.x + obj->rect.w < 0 || obj->rect.x > SCREEN_WIDTH || obj->rect.y > SCREEN_HEIGHT || obj->rect.y + obj->rect.h < 0)
		return true;
	return false;
}

//takes texture string, velocity, xPos, yPos, width, height, bullet gameObj, animation list
bool initGameObj(gameObj* obj, int texture, int velocity, int x, int y, int w, int h)
{
	obj->rect = makeRect(x, y, w, h);
	obj->texture = texture;
	obj->velocity = velocity;
	obj->velocityMod = 1;
}
