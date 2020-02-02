#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cassert>
#include <string>
#include <vector>
#include <utility>
#include "baseObjects.h"
#include "global.h"
#include "debug.h"

#include "gameObj.h"

typedef std::vector<bool (*)(gameObj*)> animVector;
typedef std::pair<animVector, int> animPair;

// default constructor
gameObj::gameObj()
{
	rect = global::makeRect(0, 0, 1, 1);
};

// detailed constructor
// takes texture string, velocity, width, height, xPos, yPos, bullet string, bullet duration, animation list
gameObj::gameObj(std::string t, const double& vel, const int &width, const int &height, const int &xPos,const int &yPos, std::string bull, const int& dur, const std::initializer_list<animPair> &seq) 
{
	currentTexture = t;
	velocity = vel;
	bullet = bull;
	duration = dur;
	animationSequence = seq;
	rect = global::makeRect(xPos, yPos, width, height);
	initialX = xPos;
	initialY = yPos;
};

// copy constructor with rect coords
// takes rhs gameObj, xPos, yPos, animation sequence
gameObj::gameObj(const gameObj& other, const int &xPos, const int &yPos, const std::vector<animPair> &seq)
{
	currentTexture = other.currentTexture;
	velocity = other.velocity;
	bullet = other.bullet;
	animationSequence = seq;
	
	rect = global::makeRect(xPos, yPos, other.rect.w, other.rect.h);
	initialX = rect.x;
	initialY = rect.y;
	duration = other.duration;
};

void gameObj::addAnimationSet(const std::vector<bool (*)(gameObj*)> &set, const int &distance)
{
	animationSequence.push_back({set, distance});
};

void gameObj::playAnimations()
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
};

bool gameObj::isOffscreen() const {
	if (getRectR() < 0 || getRectL() > global::SCREEN_WIDTH || getRectTop() > global::SCREEN_HEIGHT || getRectBottom() < 0)
		return true;
	return false;
};

// get bullet
gameObj gameObj::getBulletCopy()
{ 
	assert(bullet != "");
	gameObj newBullet = baseBullets[bullet]; // copy of bullet
	newBullet.rect.x =  rect.x + rect.w/2 - 8; // center bullet
	newBullet.rect.y = rect.y;

	return newBullet;
}
