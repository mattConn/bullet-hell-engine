sdl-game: *.cpp
	clang++ -std=c++11 -I /usr/include/SDL2/ -l SDL2 -l SDL2_image $^ -o $@

check:
	gpp config/waves.pre -o config/waves.conf && ./sdl-game

clean:
	rm sdl-game
