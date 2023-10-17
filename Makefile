CC = g++
CFLAGS = -W -Wall -Werror -std=c++20
CDEBUGFLAGS = -W -Wall -std=c++20
INC = -Iinclude
SRC = $(wildcard src/*.cpp)
EXEC = main

ifeq ($(OS),Windows_NT)
	UNAME_S = Windows
	LIB = -L./lib -lmingw32 -lSDL2main -lSDL2
else
	UNAME_S = $(shell uname -s)
	LIB = -lSDL2
endif

main:
	$(CC) $(CFLAGS) $(SRC) $(INC) $(LIB) -o $(EXEC).out
	./$(EXEC).out

debug:
	$(CC) $(CDEBUGFLAGS) $(SRC) $(INC) $(LIB) -o $(EXEC).out
	./$(EXEC).out