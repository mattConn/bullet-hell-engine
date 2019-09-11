#sdl-game: *.cpp
	#gcc -std=c11 -I /usr/include/SDL2/ -l SDL2 -l SDL2_image $^ -o $@

sdl-game:
	gcc -std=c11 -I /usr/include/SDL2/ -l SDL2 -l SDL2_image global.c main.c gameObj.c getInput.c -o game.o

check:
	./sdl-game

clean:
	rm sdl-game
