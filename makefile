CC=gcc
CFLAGS=-std=c17 -I./include
LDFLAGS=-lm -lSDL2 -lSDL2_image
PROJECT_NAME=program

SOURCE_FILES=$(wildcard src/*.c)

build: main.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(PROJECT_NAME) main.c $(SOURCE_FILES)

clean:
	rm -f $(PROJECT_NAME)
