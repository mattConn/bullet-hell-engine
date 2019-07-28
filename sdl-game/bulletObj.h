#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "texture.h"
#include "global.h"
#include "gameObj.h"

class bulletObj : public gameObj {
private:
	int duration = 0;
	int timeout = 0;

public:
	bulletObj() : gameObj() {}
	bulletObj(SDL_Texture* t, const double& vel, const int& xPos, const int& yPos, const int& width, const int& height, const int &d) : gameObj(t, vel, xPos, yPos, width, height), duration(d){}
	
	// accessors
	int getTimeout() { return timeout; }
	int getDuration() { return duration; }

	// mutators
	void setDuration(const int d) { duration = d; }
	void resetTimeout() { timeout = SDL_GetTicks() + duration; }
};