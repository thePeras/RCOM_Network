CC = gcc

DEBUG_LEVEL=2

CFLAGS = -Wall -g -D _DEBUG=$(DEBUG_LEVEL)

SRC = src/
INCLUDE = include/
BIN = bin/

HOST=ftp.up.pt
FILENAME=Release
FILE=pub/kodi/apt/pre-release/ios/$(FILENAME)

#HOST=rcom:rcom@netlab1.fe.up.pt
#FILENAME=crab.mp4
#FILE=$(FILENAME)

#HOST=ftp.up.pt
#FILENAME=elisp-manual-21-2.8.tar.gz
#FILE=pub/gnu/emacs/$(FILENAME)

#HOST=demo:password@test.rebex.net
#FILENAME=readme.txt
#FILE=$(FILENAME)

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
	rm -f $(FILENAME)