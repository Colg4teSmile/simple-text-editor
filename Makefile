CC = gcc
CFLAGS = -Wall -g -o
PACKAGE = $(shell pkg-config --cflags --libs gtk+-3.0)
LIBS = $(shell pkg-config --libs gtk+-3.0)
OUTPUT = text_editor

SRC = main.c gap_buffer.c tools.c gui.c

build: $(SRC)
	$(CC) $(PACKAGE) $(SRC) $(LIBS) $(CFLAGS) $(OUTPUT) 