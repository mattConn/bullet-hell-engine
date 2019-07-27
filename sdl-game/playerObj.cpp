#include <SDL2/SDL.h>
#include "global.h"
#include "debug.h"
#include "playerObj.h"

// player object definitions
// =========================

playerObj::playerObj() // default constructor
{
    velocity = 10;

    rect = global::makeRect(0, 0, 50);

    // load all keyPress images
    keypressTextures[global::KEY_PRESS_DEFAULT] = global::loadTexture("hello_world.bmp");
    keypressTextures[global::KEY_PRESS_UP] = global::loadTexture("arrows_up.bmp");
    keypressTextures[global::KEY_PRESS_DOWN] = global::loadTexture("arrows_down.bmp");
    keypressTextures[global::KEY_PRESS_LEFT] = global::loadTexture("arrows_left.bmp");
    keypressTextures[global::KEY_PRESS_RIGHT] = global::loadTexture("arrows_right.bmp");

    currentTexture = keypressTextures[global::KEY_PRESS_LEFT];
}

// custom constructor: sets x, y, velocity, rect
playerObj::playerObj(const int &xPos, const int &yPos, const double &vel, const int &width, const int &height) : playerObj()
{
    rect = global::makeRect(xPos, yPos, width, height);
    velocity = vel;

    currentTexture = keypressTextures[global::KEY_PRESS_UP];
}

// =============================
// end player object definitions
