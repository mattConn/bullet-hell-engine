#include <SDL.h>
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
        i = nullptr;

    rect = g::makeRect(0, 0, 50);
    jumpMaxHeight = 50*2;
}

// custom constructor: sets x, y, velocity, rect
playerObj::playerObj(const int &xPos, const int &yPos, const int &vel, const int &width, const int &height)
{
    collidable = true;
    objType = g::OBJ_PLAYER;

    rect = g::makeRect(xPos, yPos, width, height);

    jumpMaxHeight = 300;

    // set all sides to no collision
    for (auto i : sideCollision)
        i = nullptr;

    velocity = vel;

    // load all keyPress images
    keypressTextures[KEY_PRESS_DEFAULT] = g::loadTexture("hello_world.bmp");
    keypressTextures[KEY_PRESS_UP] = g::loadTexture("arrows_up.bmp");
    keypressTextures[KEY_PRESS_DOWN] = g::loadTexture("arrows_down.bmp");
    keypressTextures[KEY_PRESS_LEFT] = g::loadTexture("arrows_left.bmp");
    keypressTextures[KEY_PRESS_RIGHT] = g::loadTexture("arrows_right.bmp");
}

// check for collision
bool playerObj::checkCollision(std::vector<gameObj*> &objVector)
{
    bool collision = false;

    SDL_Rect lastPos;
    lastPos.x = rect.x;
    lastPos.y = rect.y;

    for(auto obj : objVector)
    {

        // bottom collision
        if(getRectBottom() >= obj->getRectTop() && getRectTop() < obj->getRectBottom() && getRectR() >= obj->getRectL() && getRectL() <= obj->getRectR())
        {
            rect.y -= abs(getRectBottom() - obj->getRectTop()); // clipping correction
            sideCollision[RECT_BOTTOM] = true;
        }
        else
        {
            sideCollision[RECT_BOTTOM] = false; // reset bottom collision
        }
    } // end foreach

    // set collision bool
    for(int i = 0; i < RECT_TOTAL; i++)
    {
        if(sideCollision[i])
        {
            collision = true;
            break;
        }
    }
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

// =============================
// end player object definitions
