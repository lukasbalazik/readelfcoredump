CC=gcc
CFLAGS=-Wall
SRC=src/main.c src/core.c

all: readelf32 readelf64

readelf32: $(SRC)
	$(CC) -o $@ $^ $(CFLAGS) -DARCH32

readelf64: $(SRC)
	$(CC) -o $@ $^ $(CFLAGS)


.PHONY: clean

clean:
	rm -f src/*.o readelf32 readelf64
