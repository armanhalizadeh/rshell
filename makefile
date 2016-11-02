#defining compiler
CC = g++
#defining flasgs
CFLAGS = -Wall -Werror -ansi -pedantic
#define sources
SRC = $(wildcard src/*.cpp)
OBJ = $(subst src/,bin/,$(subst .cpp,.o,$(SRC)))

all: directories bin/rshell

directories: bin/

bin/:
	mkdir -p bin/

bin/rshell: $(OBJ)
	$(CC) $(OBJ) -o bin/rshell

bin/%.o: src/%.cpp
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -R bin/
