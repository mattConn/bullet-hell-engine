#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "global.h"

// any game object
// ===============
class gameObj {
protected:

	SDL_Texture *currentTexture = nullptr;

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
		rect = g::makeRect(0, 0, 1);
	}
	gameObj(const char textureName[],  const int &xPos, const int &yPos, const int &width, const int &height = -1)
	{
		currentTexture = g::loadTexture(textureName);
		rect = g::makeRect(xPos, yPos, width, height);
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

	// get rect sides
	int getRectTop(){ return rect.y; }
	int getRectBottom(){ return rect.y + rect.h; }
	int getRectL() { return rect.x; }
	int getRectR() { return rect.x + rect.w; }


	// mutators
	void incRectX(const int n) { rect.x += n; }
	void incRectY(const int n) { rect.y += n; }

	void decRectX(const int n) { rect.x += n; }
	void decRectY(const int n) { rect.y += n; }
};
