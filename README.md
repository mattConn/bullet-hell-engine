# Shmup Game Engine
Making a shmup game engine with SDL2. A shmup (shoot-em-up) is a game like Space Invaders.

This project depends on SDL2 and SDL2_image. I followed along with Lazy Foo's tutorial to get started.

## Compiling
On Mac and Linux, use the makefile in `sdl-game`.

On Windows, open the solution file in the top-level directory with Visual Studio. 

# Documentation

<h2 id="header-files">Header Files</h2>
Specified in each summary is if the header file contains prototypes/declarations or definitions. If it does not contain definitions, there will be a corresponding source (.cpp) file.

- <a href="#animation.h">animation.h</a>
- <a href="#baseObjects.h">baseObjects.h</a>
- <a href="#configFromFile.h">configFromFile.h</a>
- <a href="#enemyWaves.h">enemyWaves.h</a>
- <a href="#getPlayerInput.h">getPlayerInput.h</a>
- <a href="#renderBullets.h">renderBullets.h</a>
- <a href="#animSequence.h">animSequence.h</a>
- <a href="#bulletContainers.h">bulletContainers.h</a>
- <a href="#debug.h">debug.h</a>
- <a href="#gameObj.h">gameObj.h</a>
- <a href="#global.h">global.h</a>
- <a href="#renderEnemies.h">renderEnemies.h</a>

<h3 id="animation.h">animation.h</h3>
Animation function prototypes.
<small><a href="#header-files">[Top]</a></small>

<h3 id="baseObjects.h">baseObjects.h</h3>
`baseBullets` and `baseEnemies` maps. Bullets and enemies are cloned from here.
<small><a href="#header-files">[Top]</a></small>

<h3 id="configFromFile.h">configFromFile.h</h3>
Prototypes for functions to read text config files for bullets, enemies and waves and fill in `baseBullets`, `baseEnemies` and `enemyWaves` with their respective objects. Functions are `bulletsFromFile`, `enemiesFromFile`, and `wavesFromFile`.
<small><a href="#header-files">[Top]</a></small>

<h3 id="enemyWaves.h">enemyWaves.h</h3>
2D vector of `gameObj`s, `enemyWaves`, to be filled with enemy clones.
<small><a href="#header-files">[Top]</a></small>

<h3 id="getPlayerInput.h">getPlayerInput.h</h3>
Definition for `getPlayerInput` function which checks the keystate of pertinent keyboard keys to control the player and update the state of the game.
<small><a href="#header-files">[Top]</a></small>

<h3 id="renderBullets.h">renderBullets.h</h3>
Definition for `renderBullets`, a function to control position of current bullets and update renderer with current bullets.
<small><a href="#header-files">[Top]</a></small>

<h3 id="animSequence.h">animSequence.h</h3>
typedefs for function pointer vectors (`animVector`) and `std::pair`s of `animVectors` and distance integers (`animPair`).
<small><a href="#header-files">[Top]</a></small>

<h3 id="bulletContainers.h">bulletContainers.h</h3>
`gameObj` vectors `currentPlayerBullets` and `currentEnemyBullets`, which will contain bullet clones. These manage bullets on screen.
<small><a href="#header-files">[Top]</a></small>

<h3 id="debug.h">debug.h</h3>
`DEBUG_MSG` macro for writing debug messages to stdout. Undefine `DEBUG` in this header file before compiling to supress these messages.
<small><a href="#header-files">[Top]</a></small>

<h3 id="gameObj.h">gameObj.h</h3>
Definition for `SDL_Rect` wrapper class used for all entities in the engine. Manages position, width/height, texture and animations for a given entity clone. Provides interface for getting/setting underlying `SDL_Rect` properties and the aforementioned properties.
<small><a href="#header-files">[Top]</a></small>

<h3 id="global.h">global.h</h3>
Function prototypes to init SDL subsystems and prototypes for SDL helper functions.
<small><a href="#header-files">[Top]</a></small>

<h3 id="renderEnemies.h">renderEnemies.h</h3>
Definition for function that manages enemies on screen; their positions, animations, and checking if offscreen.
<small><a href="#header-files">[Top]</a></small>
