CC = gcc

DEBUG_LEVEL=2

CFLAGS = -Wall -g -D _DEBUG=$(DEBUG_LEVEL)

SRC = src/
INCLUDE = include/
BIN = bin/

#HOST=rcom:rcom@netlab1.fe.up.pt
HOST=ftp.up.pt

FILE=files/crab.mp4

# Targets
.PHONY: all
all: $(BIN)/main

$(BIN)/main: main.c $(SRC)/*.c
	$(CC) $(CFLAGS) -o $@ $^ -I$(INCLUDE)

.PHONY: run
run: $(BIN)/main
	./$(BIN)/main "ftp://$(HOST)/$(FILE)"

.PHONY: clean
clean:
	rm -f $(BIN)/main