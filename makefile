CC = gcc
OPTS = -Wall -Wextra
LINK = -g -lm
#LINK = -g -fsanitize=address -fsanitize=leak -lm
BOUT = build
SRC = src
LIBS = -lSDL2

all: main.o gfx.o vec.o util.o particles.o
	$(CC) $(BOUT)/main.o $(BOUT)/gfx.o $(BOUT)/vec.o $(BOUT)/util.o $(BOUT)/particles.o $(LIBS) $(LINK) -o $(BOUT)/prog


pre-build: 
	mkdir -p build

main.o: pre-build $(SRC)/main.c
	$(CC) $(OPTS) -c $(SRC)/main.c -o $(BOUT)/main.o

gfx.o: pre-build $(SRC)/gfx.c
	$(CC) $(OPTS) -c $(SRC)/gfx.c -o $(BOUT)/gfx.o

vec.o: pre-build $(SRC)/vec.c
	$(CC) $(OPTS) -c $(SRC)/vec.c -o $(BOUT)/vec.o

util.o: pre-build $(SRC)/util.c
	$(CC) $(OPTS) -c $(SRC)/util.c -o $(BOUT)/util.o

particles.o: pre-build $(SRC)/particles.c
	$(CC) $(OPTS) -c $(SRC)/particles.c -o $(BOUT)/particles.o

clean:
	rm -r build
