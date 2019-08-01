sdl-game: *.cpp
	clang++ -std=c++11 -I /usr/include/SDL2/ -l SDL2 -l SDL2_image $^ -o $@

sdl-game.html: *.cpp
	em++ -std=c++11 --use-preload-plugins -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["bmp","png"]' --emrun $^ -o $@

check:
	./sdl-game

check-html:
	emrun --no_browser --port 8000 ./sdl-game.html

clean:
	rm sdl-game*
