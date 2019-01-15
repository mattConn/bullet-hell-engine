#pragma once

#include <SDL.h>
#include <SDL_image.h>
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

	// min width and height of collision rectangles
	const int MIN_COLLISION_H = 12;
	const int MIN_COLLISION_W = 5;

	int velocity; // player velocity
    bool sideCollision[RECT_TOTAL]; // list of objects on side of collision
	moveType movement = MOVE_NONE; // player movement

	// jump data members
	bool jumping = false; // currently jumping or not
	unsigned int jumpStartTime = 0; // time jump starts
	unsigned int jumpStartPos = 0; // y position of jump start
	unsigned int jumpMaxHeight; // max jump height

	// min. delay between current time and jump time
	const unsigned int JUMP_MIN_DELAY = 50;

	// textures for keypresses
	SDL_Texture *keypressTextures[KEY_PRESS_TOTAL];

public:
	playerObj(); // default constructor
	playerObj(const int &xPos, const int &yPos, const int &vel, const int &width, const int &height = -1);

	bool checkCollision(std::vector<gameObj*> &objVector); // check for collision

	void checkKeyState(); // check keystate
	void updatePhysics(); // update physics based on flags
};
