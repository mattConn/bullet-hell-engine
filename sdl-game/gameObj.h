#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cassert>
#include <string>
#include "global.h"

class bulletObj;

// any game object
// ===============
class gameObj {
private:

	std::string currentTexture;

	static gameObj bullet; // defined in gameObj.cpp

	// fire rate members
	int duration = 0; // duration of old bullet on screen
	int timeout = 0; // time before bullet shoul be fired

	SDL_Rect rect; // obj rect (used for coordinates)
	double velocity = 1;
	double velocityMod = 1;

	// starting position
	int initialX = 0;
	int initialY = 0;

	bool (*animation)(gameObj *) = nullptr;

public:
	// default constructor
	gameObj()
	{
		rect = global::makeRect(0, 0, 1, 1);
	}
	gameObj(std::string t, const double& vel, const int &xPos, const int &yPos, const int &width, const int &height) : currentTexture(t), velocity(vel)
	{
		rect = global::makeRect(xPos, yPos, width, height);
		setInitialX(xPos);
		setInitialY(yPos);
	}

	// accessors
	std::string getCurrentTexture() const
	{
		return currentTexture;
	}

	void setCurrentTexture(std::string t)
	{
		currentTexture = t;
	}

	void setAnimation(bool (*anim)(gameObj*) ) { animation = anim; }
	bool playAnimation()
	{
		assert(animation != nullptr);
		return animation(this); 
	}

	bool isOffscreen() const {
		if (getRectR() < 0 || getRectL() > global::SCREEN_WIDTH || getRectTop() > global::SCREEN_HEIGHT || getRectBottom() < 0)
			return true;
		return false;
	}

	// get velocity
	double getVelocity() const { return velocity; }
	double getVelocityMod() const { return velocityMod; }

	void setVelocityMod(const double& v) { velocityMod = v; }

	// get rect sides
	int getRectTop() const { return rect.y; }
	int getRectBottom() const { return rect.y + rect.h; }
	int getRectL() const { return rect.x; }
	int getRectR() const { return rect.x + rect.w; }

	int getRectX() const { return rect.x; }
	int getRectY() const { return rect.y; }

	void setRectX(const int &x) { rect.x = x; }
	void setRectY(const int &y) { rect.y = y; }

	SDL_Rect *getRectPtr() { return &rect; }

	// get initial position
	int getInitialX() const { return initialX; }
	int getInitialY() const { return initialY; }
	
	// set initial position
	void setInitialX(const int& x) { initialX = x; };
	void setInitialY(const int& y) { initialY = y; };

	void setInitialPos(const int& x, const int& y)
	{
		setInitialX(x);
		setInitialY(y);
	}

	// get fire rate info
	int getDuration() const { return duration; }
	int getTimeout() const { return timeout; }

	// set fire rate info
	void setDuration(const int& d) { duration = d; }
	void resetTimeout() { timeout = duration + SDL_GetTicks(); }

	// get bullet
	gameObj getBulletCopy()
	{ 
		gameObj newBullet = gameObj(bullet); // copy of bullet
		newBullet.setRectX(getRectX());
		newBullet.setRectY(getRectY());

		return newBullet;
	}

	gameObj* getBulletPtr() const { return &bullet; }

	// set bullet
	void setBullet(std::string t, const double& vel, const int& width, const int& height, const int& d)
	{
		bullet = gameObj(t, vel, 0, 0, width, height);
		bullet.duration = d;
		bullet.timeout = d + SDL_GetTicks();
	}

	// mutators
	void incRectX(const int n) { rect.x += n; }
	void incRectY(const int n) { rect.y += n; }

	void decRectX(const int n) { rect.x -= n; }
	void decRectY(const int n) { rect.y -= n; }

};
