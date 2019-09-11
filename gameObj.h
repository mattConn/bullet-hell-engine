#pragma once

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "global.h"

typedef struct GameObj {

	int texture;

	//gameObj *bullet = NULL;

	// fire rate members
	int duration; // duration of old bullet on screen
	int timeout; // time before bullet shoul be fired (SDL_GetTicks() + duration)

	SDL_Rect rect; // obj rect (used for coordinates)
	double velocity;
	double velocityMod;

	// starting position
	int initialX;
	int initialY;

	// sequence of animations: pair of vector and duration
	//std::vector<animPair> animationSequence;

/*
public:
	// default constructor
	gameObj()
	{
		rect = global::makeRect(0, 0, 1, 1);
	}

	// detailed constructor
	// takes texture string, velocity, xPos, yPos, width, height, bullet gameObj, animation list
	gameObj(std::string t, const double& vel, const int &xPos, const int &yPos, const int &width, const int &height, gameObj *bull = nullptr, const std::initializer_list<animPair> &seq = {}) : currentTexture(t), velocity(vel), bullet(bull), animationSequence(seq)
	{
		rect = global::makeRect(xPos, yPos, width, height);
		setInitialX(xPos);
		setInitialY(yPos);
	}

	// bullet constructor
	gameObj(std::string t, const double& vel, const int &width, const int &height, const int &dur) : currentTexture(t), velocity(vel)
	{
		rect = global::makeRect(0, 0, width, height);
		duration = dur;
		timeout = dur + SDL_GetTicks();
	}

	// copy constructor with rect coords
	// takes rhs gameObj, xPos, yPos, animation sequence
	gameObj(const gameObj* other, const int &xPos, const int &yPos, const std::vector<animPair> &seq = {}) : currentTexture(other->currentTexture), velocity(other->velocity), bullet(other->bullet), animationSequence(seq)
	{
		rect = global::makeRect(xPos, yPos, other->rect.w, other->rect.h);
		initialX = rect.x;
		initialY = rect.y;
	}

	// bullet ptrs copied over from baseBullets; these are freed during close routine
*/
	/*
	~gameObj()
	{
		delete bullet;
		bullet = nullptr;
	}
	*/

/*
	// accessors
	std::string getCurrentTexture() const
	{
		return currentTexture;
	}
*/

/*
	void setCurrentTexture(std::string t)
	{
		currentTexture = t;
	}
*/

/*
	void addAnimationSet(const std::initializer_list<bool (*)(gameObj*)> &set, const int &distance = 0)
	{
		animationSequence.push_back({set, distance});
	}
*/

/*
	void playAnimations()
	{
		if (animationSequence.size() == 0) return;

		auto currentRow = animationSequence.front(); // row of animation, distance pair

		// if no duration specified or distance traveled < distance needed, play animations
		if (currentRow.second <= 0 || (abs(rect.x - initialX) < currentRow.second && abs(rect.y - initialY) < currentRow.second) )
		{
			for (auto& anim : currentRow.first)
				anim(this);
		}
		else // erase row, reset initial coords
		{
			animationSequence.erase(animationSequence.begin());
			initialX = rect.x;
			initialY = rect.y;
		}
	}
*/

} gameObj;

// check if gameObj is offscreen
bool isOffscreen(gameObj* obj);
bool initGameObj(gameObj* obj, int texture, int velocity, int w, int h);


