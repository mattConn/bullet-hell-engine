# compiles on *nix

COMPILER = clang++
FLAGS = -std=c++11
BIN = game
INCLUDE = -I sdl2/2.0.9/include/SDL2/ -I sdl2_image/2.0.4/include/SDL2/
LIB = -l SDL2 -l SDL2_image

$(BIN): main.cpp
	$(COMPILER) $(FLAGS) main.cpp -o $(BIN) $(INCLUDE) $(LIB) && ./$(BIN)

clean:
	rm $(BIN)
