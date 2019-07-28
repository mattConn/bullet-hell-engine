#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "texture.h"
#include "global.h"

// any game object
// ===============
class gameObj {
private:

	SDL_Texture *currentTexture = nullptr;
	SDL_Rect rect; // obj rect (used for coordinates)
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
	gameObj(const texture *t, const double& vel, const int &xPos, const int &yPos, const int &width, const int &height) : velocity(vel)
	{
		rect = global::makeRect(xPos, yPos, width, height);
		currentTexture = t->getLoadedTexture();
	}

	// destructor
	~gameObj() 
	{
		SDL_DestroyTexture(currentTexture);
		currentTexture = nullptr;
	}

	// accessors
	SDL_Texture *getCurrentTexture()
	{
		return currentTexture;
	}

	void setCurrentTexture(const texture *t)
	{
		currentTexture = t->getLoadedTexture();
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

	int getRectX() { return rect.x; }
	int getRectY() { return rect.y; }

	void setRectX(const int &x) { rect.x = x; }
	void setRectY(const int &y) { rect.y = y; }

	SDL_Rect getRect() { return rect; }

	// mutators
	void incRectX(const int n) { rect.x += n; }
	void incRectY(const int n) { rect.y += n; }

	void decRectX(const int n) { rect.x -= n; }
	void decRectY(const int n) { rect.y -= n; }
};
