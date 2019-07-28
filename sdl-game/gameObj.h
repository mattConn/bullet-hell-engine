#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "global.h"

// any game object
// ===============
class gameObj {
protected:

	SDL_Texture *currentTexture = nullptr;
	double velocity = 1;
	double velocityMod = 1;

	// rectangle sides
	enum rectSides
	{
		RECT_L,
		RECT_R,
		RECT_TOP,
		RECT_BOTTOM,
		RECT_TOTAL
	};

public:
	// default constructor
	gameObj()
	{
		rect = global::makeRect(0, 0, 1, 1);
	}
	gameObj(SDL_Texture *texture, const double& vel, const int &xPos, const int &yPos, const int &width, const int &height) : currentTexture(texture), velocity(vel)
	{
		rect = global::makeRect(xPos, yPos, width, height);
	}

	// destructor
	~gameObj() 
	{
		SDL_DestroyTexture(currentTexture);
		currentTexture = nullptr;
	}

	// obj rect
	SDL_Rect rect;

	// accessors
	SDL_Texture *getCurrentTexture()
	{
		return currentTexture;
	}

	void setCurrentTexture(SDL_Texture *texture)
	{
		currentTexture = texture;
	}

	bool isOffscreen() {
		if (getRectR() < 0 || getRectL() > global::SCREEN_WIDTH || getRectTop() > global::SCREEN_HEIGHT || getRectBottom() < 0)
			return true;
		return false;
	}

	// get velocity
	double getVelocity() { return velocity; }
	double getVelocityMod() { return velocityMod; }

	void setVelocityMod(const double& v) { velocityMod = v; }

	// get rect sides
	int getRectTop(){ return rect.y; }
	int getRectBottom(){ return rect.y + rect.h; }
	int getRectL() { return rect.x; }
	int getRectR() { return rect.x + rect.w; }

	// mutators
	void incRectX(const int n) { rect.x += n; }
	void incRectY(const int n) { rect.y += n; }

	void decRectX(const int n) { rect.x -= n; }
	void decRectY(const int n) { rect.y -= n; }
};
