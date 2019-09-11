#include <stdbool.h>
#include "gameObj.h"

bool isOffscreen(gameObj* obj)
{
	if (obj->rect.x + obj->rect.w < 0 || obj->rect.x > SCREEN_WIDTH || obj->rect.y > SCREEN_HEIGHT || obj->rect.y + obj->rect.h < 0)
		return true;
	return false;
}

//takes texture string, velocity, xPos, yPos, width, height, bullet gameObj, animation list
gameObj* makeGameObj(int texture, int velocity, int w, int h)
{
	static gameObj obj;
	obj.rect.w = w;
	obj.rect.h = h;
	obj.initialX = obj.initialY = 0;
	obj.duration = obj.timeout = 0;
	obj.texture = texture;
	obj.velocity = velocity;
	obj.velocityMod = 1;

	return &obj;
}
