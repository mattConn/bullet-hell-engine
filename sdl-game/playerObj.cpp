#include <SDL2/SDL.h>
#include "global.h"
#include "debug.h"
#include "playerObj.h"

// player object definitions
// =========================

playerObj::playerObj() // default constructor
{
    velocity = 10;

    rect = g::makeRect(0, 0, 50);

    // load all keyPress images
    keypressTextures[KEY_PRESS_DEFAULT] = g::loadTexture("hello_world.bmp");
    keypressTextures[KEY_PRESS_UP] = g::loadTexture("arrows_up.bmp");
    keypressTextures[KEY_PRESS_DOWN] = g::loadTexture("arrows_down.bmp");
    keypressTextures[KEY_PRESS_LEFT] = g::loadTexture("arrows_left.bmp");
    keypressTextures[KEY_PRESS_RIGHT] = g::loadTexture("arrows_right.bmp");

    currentTexture = keypressTextures[KEY_PRESS_LEFT];
}

// custom constructor: sets x, y, velocity, rect
playerObj::playerObj(const int &xPos, const int &yPos, const double &vel, const int &width, const int &height, const KeyPresses &direction) : playerObj()
{
    rect = g::makeRect(xPos, yPos, width, height);
    velocity = vel;

    currentTexture = keypressTextures[direction];
}

// =============================
// end player object definitions
