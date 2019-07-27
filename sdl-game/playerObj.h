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

	int velocity; // player velocity
    bool sideCollision[RECT_TOTAL]; // list of objects on side of collision
	moveType movement = MOVE_NONE; // player movement

	// textures for keypresses
	SDL_Texture *keypressTextures[KEY_PRESS_TOTAL];

public:
	playerObj(); // default constructor
	playerObj(const int &xPos, const int &yPos, const int &vel, const int &width, const int &height = -1, const KeyPresses &direction = KEY_PRESS_RIGHT);

	void checkCollision(std::vector<gameObj*> &objVector); // check for collision
	void resetCollision();
	void updatePhysics(std::vector<gameObj*>& objVector); // update physics based on flags


	// wrapper for player state functions
	void getUserInput(std::vector<gameObj*>& objVector);
	void updateWorldPosition(std::vector<gameObj*>& objVector, const int x = 0, const int y = 0);
};
