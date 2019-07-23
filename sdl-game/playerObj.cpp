#include <SDL2/SDL.h>
#include "global.h"
#include "debug.h"
#include "playerObj.h"

// player object definitions
// =========================

playerObj::playerObj() // default constructor
{
    collidable = true;
    objType = g::OBJ_PLAYER;
    velocity = 10;

    // set all sides to no collision
    for (auto i : sideCollision)
        i = false;

    rect = g::makeRect(0, 0, 50);
    jumpMaxHeight = 300;

    // load all keyPress images
    keypressTextures[KEY_PRESS_DEFAULT] = g::loadTexture("hello_world.bmp");
    keypressTextures[KEY_PRESS_UP] = g::loadTexture("arrows_up.bmp");
    keypressTextures[KEY_PRESS_DOWN] = g::loadTexture("arrows_down.bmp");
    keypressTextures[KEY_PRESS_LEFT] = g::loadTexture("arrows_left.bmp");
    keypressTextures[KEY_PRESS_RIGHT] = g::loadTexture("arrows_right.bmp");

    currentTexture = keypressTextures[KEY_PRESS_LEFT];
}

// custom constructor: sets x, y, velocity, rect
playerObj::playerObj(const int &xPos, const int &yPos, const int &vel, const int &width, const int &height, const KeyPresses &direction) : playerObj()
{
    rect = g::makeRect(xPos, yPos, width, height);
    velocity = vel;

    currentTexture = keypressTextures[direction];
}

// check for collision
bool playerObj::checkCollision(std::vector<gameObj*> &objVector)
{
    bool collision = false;

    for(int i = 0; i < RECT_TOTAL; i++) // reset side collision
        sideCollision[i] = false;

    SDL_Rect intersection; // intersection rect

    for(auto obj : objVector)
    {
        if(SDL_IntersectRect(&rect, &obj->rect, &intersection))
        {
            collision = true;

            if(obj->getRectTop() >= getRectTop()) // bottom collision
            {
                rect.y -= intersection.h-1;
                sideCollision[RECT_BOTTOM] = true;
            }

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

        }

    } // end foreach


    return collision;
}

void playerObj::checkKeyState()
{

    // check keystate
    //===============

    // move left
    if (g::keyState[SDL_SCANCODE_LEFT])
    {
        currentTexture = keypressTextures[KEY_PRESS_LEFT];

        // if no left-side collision, move left
        if (!sideCollision[RECT_L])
            movement = MOVE_L;

    }
    // move right
    else if (g::keyState[SDL_SCANCODE_RIGHT])
    {
        currentTexture = keypressTextures[KEY_PRESS_RIGHT];

        // if no right-side collision, move right
        if (!sideCollision[RECT_R])
            movement = MOVE_R;
    }
    else
        movement = MOVE_NONE;

    // jump
    // if bottom collision and not already jumping
    // and the difference between current time and time of jump is small enough (SDL_GetTicks == jumpStartTime not possible).
    //	(This time check is necessary to prevent key repeat.)
    if (g::keyState[SDL_SCANCODE_Z] && !jumping && sideCollision[RECT_BOTTOM] && SDL_GetTicks() - jumpStartTime < JUMP_MIN_DELAY)
        jumping = true;
    else if (!g::keyState[SDL_SCANCODE_Z])
    {
        jumpStartPos = rect.y;
        jumpStartTime = SDL_GetTicks();
        jumping = false;
    }

}

void playerObj::updatePhysics()
{
    // directional movement
    // ====================
    switch (movement)
    {
    case MOVE_L:
        rect.x -= velocity;
        break;
    case MOVE_R:
        rect.x += velocity;
        break;
    default:
        break;
    }

    // gravity/falling
    // ===============

    // if no bottom collision and not jumping, fall
    if (!sideCollision[RECT_BOTTOM] && !jumping)
        rect.y += velocity * 2;

    // jumping
    // =======

    // If jumping and jumping height is less than max jump height and no top collision
    if (jumping && !sideCollision[RECT_TOP] && jumpStartPos - rect.y < jumpMaxHeight)
        rect.y -= velocity * 3;
    else // set jumping to false after jumpMaxHeight
        jumping = false;

}

// wrapper for player state functions
void playerObj::updatePlayer(std::vector<gameObj*>& objVector)
{
	checkCollision(objVector);
	checkKeyState();
	updatePhysics();
}

// =============================
// end player object definitions
