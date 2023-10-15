# CC = g++
# CFLAGS = -W -Wall -Werror
# INC = -Iinclude
# SRC = $(wildcard src/*.cpp)
# EXEC = main

# ifeq ($(OS),Windows_NT)
# 	UNAME_S = Windows
# 	LIB = -L./lib -lmingw32 -lSDL2main -lSDL2 -lglew32 -lopengl32
# else
# 	UNAME_S = $(shell uname -s)
# 	LIB = -lSDL2 -lGLEW -lGL
# endif

# main:
# 	$(CC) $(CFLAGS) $(SRC) $(INC) $(LIB) -o $(EXEC)
# 	./$(EXEC)

# debug:
# 	$(CC) -W -Wall -g $(SRC) $(INC) $(LIB) -o $(EXEC)
# 	./$(EXEC)

CC = g++
CFLAGS = -W -Wall -Werror
INC = -Iinclude
SRC = $(wildcard src/*.cpp)
EXEC = main

main:
	$(CC) $(CFLAGS) $(SRC) $(INC) -o $(EXEC)
	./$(EXEC)

debug:
	$(CC) -W -Wall -g $(SRC) $(INC) -o $(EXEC)
	./$(EXEC)

