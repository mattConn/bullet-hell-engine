CC = gcc
BIN = sdl-game
FLAGS = -std=c11 -I /usr/include/SDL2/ -l SDL2 -l SDL2_image -D DEBUG -g

sdl-game: global.c main.c entity.c
	$(CC) $(FLAGS) $^ -o $@

check:
	./$(BIN)

clean:
	rm $(BIN)
