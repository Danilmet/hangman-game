CC = g++
CFLAGS = -Wall -Werror

EXECUTABLE = bin/deposit

DIRECTORY = build/src
BUILDDIR = build

all: $(DIRECTORY)/main.o $(DIRECTORY)/hangman.o
	$(CC) $(DIRECTORY)/main.cpp $(DIRECTORY)/hangman.o -o $(EXECUTABLE)

$(DIRECTORY)/main.o: src/main.cpp
	mkdir -p build
	mkdir -p build/src
	mkdir -p bin
	$(CC) $(CFLAGS) -c src/main.cpp -o $(DIRECTORY)/main.o

$(DIRECTORY)/hangman.o: src/hangman.cpp
	$(CC) $(CFLAGS) -c src/hangman.cpp -o $(DIRECTORY)/hangman.o

.PHONY: clean

clean:
	rm -rf *.o *.exe bin/* build/src/*.o
