#pragma once

#include "gameObj.h"

class bulletObj : public gameObj {
	// fire rate members
	int duration = 0; // duration of old bullet on screen
	int timeout = 0; // time before bullet shoul be fired

public:
	bulletObj() : gameObj() {};
	bulletObj(std::string t, const double& vel, const int& width, const int& height, const int& dur) : gameObj(t, vel, 0, 0, width, height), duration(dur) {};

	// get fire rate info
	int getDuration() const { return duration; }
	int getTimeout() const { return timeout; }

	// set fire rate info
	void setDuration(const int& d) { duration = d; }
	void resetTimeout() { timeout = duration + SDL_GetTicks(); }
	void setTimeout(const int& t) { timeout = t; }

	// get bullet copy at current position
	bulletObj getCopyAtPos(const gameObj &g) const
	{
		bulletObj newBullet = *this; // copy bullet
		newBullet.setRectX(g.getRectX() + g.getRectW() / 2 - 8); // center bullet
		newBullet.setRectY(g.getRectY());

		return newBullet;
	}
};