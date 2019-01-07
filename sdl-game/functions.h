#include <SDL.h>
#include <SDL_image.h>

// window dimensions
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

SDL_Window *window = nullptr; // main window
SDL_Surface *windowSurface = nullptr; // surface for main window
SDL_Renderer *renderer = nullptr; // main renderer

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

bool init(SDL_Window *&window, SDL_Surface *&windowSurface); // init SDL subsystems, windows etc.
SDL_Surface *loadImage(char fileName[]); // load image and optimize
SDL_Texture *loadTexture(const char filename[]); // load image and convert to texture
SDL_Rect getRect(const float &x, const float &y, const float &w, const float &h); // make SDL Rect
bool close(SDL_Surface *&surface, SDL_Window *&window); // free memory and quit SDL subsytems

bool init(SDL_Window *&window, SDL_Surface *&windowSurface)
{
	DEBUG_MSG("** Begin init **");

	// init video
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not init video: " << SDL_GetError() << std::endl;
		return false;
	}
	DEBUG_MSG("Init video");

	// init PNG loading
	if ( !IMG_Init(IMG_INIT_PNG) )
	{
		std::cout << "Could not init PNG loading: " << SDL_GetError() << std::endl;
		return false;
	}
	DEBUG_MSG("Init PNG loading");

	// create window
	window = SDL_CreateWindow("SDL Tutorial",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN);

	if (window == nullptr)
	{
		std::cout << "SDL window creation error: " << SDL_GetError() << std::endl;
		return false;
	}
	DEBUG_MSG("Created window");

	// init renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr)
	{
		std::cout << "Could not init renderer: " << SDL_GetError() << std::endl;
		return false;
	}
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	DEBUG_MSG("Init renderer");

	// assign window surface
	windowSurface = SDL_GetWindowSurface(window);

	DEBUG_MSG("** End init **");

	return true;
}

SDL_Surface *loadImage(const char fileName[])
{
	// load image
	SDL_Surface *imageSurface = IMG_Load(fileName);
	SDL_Surface *optimizedSurface = nullptr;

	if (imageSurface == nullptr)
	{
		std::cout << "Unable to load image " << fileName << ": " << SDL_GetError() << std::endl;
		return nullptr;
	}

	// optimize image
	optimizedSurface = SDL_ConvertSurface(imageSurface, windowSurface->format, 0);
	if (optimizedSurface == nullptr)
	{
		std::cout << "Unable to optimize surface " << fileName << ": " << std::endl;
		return nullptr;
	}
	
	// free unoptimized surface
	SDL_FreeSurface(imageSurface);

	DEBUG_MSG("Load image successful: " << fileName);

	return optimizedSurface;
}

//IMG_LoadTexture wrapper
SDL_Texture *loadTexture(const char fileName[])
{
	SDL_Texture *texture = IMG_LoadTexture(renderer, fileName);

	if (texture == nullptr)
	{
		std::cout << "Unable to load texture: " << fileName << " : " << SDL_GetError() << std::endl;
		return nullptr;
	}

	DEBUG_MSG("Load texture successful: " << fileName);

	return texture;
}

// SDL rect wrapper
SDL_Rect getRect(const float &xPos, const float &yPos, const float &width, const float &height = NULL)
{
	SDL_Rect rect;
	rect.x = xPos;
	rect.y = yPos;
	rect.w = width;
	rect.h = height == NULL ? width : height;

	return rect;
}

bool close(SDL_Surface *&surface, SDL_Window *&window)
{
	//Deallocate surface
	SDL_FreeSurface(surface);
	surface = nullptr;

	//Destroy window
	SDL_DestroyWindow(window);
	window = nullptr;

	// Destroy renderer
	SDL_DestroyRenderer(renderer);

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();

	DEBUG_MSG("Close successful");
	return true;
}
