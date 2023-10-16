CC = g++
CFLAGS = -W -Wall -Werror
INC = -Iinclude
SRC = $(wildcard src/*.cpp)
EXEC = main

ifeq ($(OS),Windows_NT)
	UNAME_S = Windows
	LIB = -L./lib -lmingw32 -lSDL2main -lSDL2
else
	UNAME_S = $(shell uname -s)
	LIB = -lSDL2 -lGLEW
endif

main:
	$(CC) $(CFLAGS) $(SRC) $(INC) $(LIB) -o $(EXEC)
	./$(EXEC)

debug:
	$(CC) -W -Wall -g $(SRC) $(INC) $(LIB) -o $(EXEC)
	./$(EXEC)