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

	// set all movement to false
	e->movement = false;
	for(int i = 0; i < TOTAL_MOVEMENT; i++) e->movementKind[i] = false;

	// positive direction
	e->directionSign = 1;
	
	// set collision to false
	for(int i = 0; i < TOTAL_SIDES; i++) e->collisionSide[i] = false;

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

// set collision state of entity e1 by checking for collision with e2
bool setEntityCollision(entity *e1, entity *e2)
{
	SDL_Rect intersection;

	// reset collision
	e1->collision = false;
	for(int j = 0; j < TOTAL_SIDES; j++)
		e1->collisionSide[j] = false;

	// check intersection
	if(SDL_IntersectRect(&e1->rect, &e2->rect, &intersection))
	{
		e1->collision = true;

		if(e2->rect.y >= e1->rect.y) // bottom collision
		{
			e1->rect.y -= intersection.h-1; // reposition rect
			e1->collisionSide[SIDE_BOTTOM] = true; // set collision
		}
		/*

            if(intersection.x == rect.x && intersection.y == rect.y) // top collision or left collision
            {
                if(intersection.w == rect.w) // top collision
                {
                    rect.y += intersection.h-1;
                    sideCollision[RECT_TOP] = true;
                }
                else // left collision
                {
                    rect.x += intersection.w;
                    sideCollision[RECT_L] = true;
                }
            }

            if(intersection.x > rect.x && intersection.y == rect.y) // right collision
            {
                rect.x -= intersection.w;
                sideCollision[RECT_R] = true;
            }
			*/
		}
}

bool updateEntityPhysics(entity *e)
{
	if(e->weight > 0 && !e->collisionSide[SIDE_BOTTOM])
		e->rect.y += gravity * e->weight;
}
