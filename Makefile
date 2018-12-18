CC = g++
CFLAGS = -Wall -Werror
TESTFLAGS = -I src -I thirdparty -Wall -Werror

EXECUTABLE = bin/hangman
EXECUTABLE_TESTS = bin/test

DIRECTORY = build/src
DIRECTORY_TEST = build/test
BUILDDIR = build

all: $(DIRECTORY)/main.o $(DIRECTORY)/hangman.o
	$(CC) $(DIRECTORY)/main.o $(DIRECTORY)/hangman.o -o $(EXECUTABLE)

$(DIRECTORY)/main.o: src/main.cpp
	mkdir -p build
	mkdir -p build/src
	mkdir -p build/test
	mkdir -p bin
	$(CC) $(CFLAGS) -c src/main.cpp -o $(DIRECTORY)/main.o

$(DIRECTORY)/hangman.o: src/hangman.cpp
	$(CC) $(CFLAGS) -c src/hangman.cpp -o $(DIRECTORY)/hangman.o

all: HANGMAN_TEST

HANGMAN_TEST: $(DIRECTORY)/hangman.o $(DIRECTORY_TEST)/main.o $(DIRECTORY_TEST)/hangman_test.o
	$(CC) $(DIRECTORY)/hangman.o $(DIRECTORY_TEST)/main.o $(DIRECTORY_TEST)/hangman_test.o -o $(EXECUTABLE_TESTS)

$(DIRECTORY_TEST)/main.o: test/main.c
	$(CC) $(TESTFLAGS) -c test/main.c -o $(DIRECTORY_TEST)/main.o

$(DIRECTORY_TEST)/hangman_test.o: test/hangman_test.c
	$(CC) $(TESTFLAGS) -c test/hangman_test.c -o $(DIRECTORY_TEST)/hangman_test.o


.PHONY: clean

clean:
	rm -rf *.o *.exe bin/* build/src/*.o build/test/*.o
