#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "global.h"
#include "gameObj.h"

// player object
// =============
class playerObj : public gameObj {

	double velocity; // player velocity
	double velocityMod = 1; // player velocity modifier

	// textures for keypresses
	SDL_Texture *keypressTextures[global::KEY_PRESS_TOTAL];

public:
	playerObj(); // default constructor
	playerObj(const int &xPos, const int &yPos, const double &vel, const int &width, const int &height = -1);

	double getVelocity(){ return velocity; }
	double getVelocityMod(){ return velocityMod; }

	void setVelocityMod(const double &v){ velocityMod = {v}; }
};
