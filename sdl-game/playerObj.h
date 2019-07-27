#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "global.h"
#include "gameObj.h"

// player object
// =============
class playerObj : public gameObj {

	// keypress enum for relating textures to keypress events
	enum KeyPresses
	{
		KEY_PRESS_DEFAULT,
		KEY_PRESS_UP,
		KEY_PRESS_DOWN,
		KEY_PRESS_LEFT,
		KEY_PRESS_RIGHT,
		KEY_PRESS_TOTAL
	};

	double velocity; // player velocity
	double velocityMod = 1; // player velocity modifier

	// textures for keypresses
	SDL_Texture *keypressTextures[KEY_PRESS_TOTAL];

public:
	playerObj(); // default constructor
	playerObj(const int &xPos, const int &yPos, const double &vel, const int &width, const int &height = -1, const KeyPresses &direction = KEY_PRESS_UP);

	double getVelocity(){ return velocity; }
	double getVelocityMod(){ return velocityMod; }

	void setVelocityMod(const double &v){ velocityMod = {v}; }
};
