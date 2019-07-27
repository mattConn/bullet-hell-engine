#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "global.h"

#pragma once

class texture {
		SDL_Texture *loadedTexture;
		std::string name;

public:
	texture(){ loadedTexture = nullptr; }
	texture(const char name[]) : name(name) { loadedTexture = global::loadTexture(name);}

	SDL_Texture *getLoadedTexture(){ return loadedTexture; }

	~texture()
	{
        SDL_DestroyTexture(loadedTexture);
        loadedTexture = nullptr;
	}
};
