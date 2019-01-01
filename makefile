COMPILER = clang++
BIN = game
INCLUDE = include
LIB = lib

$(BIN): main.cpp
	$(COMPILER) main.cpp -o $(BIN) -I $(INCLUDE) -L $(LIB) -l SDL2-2.0.0 && ./$(BIN)

clean:
	rm $(BIN)
