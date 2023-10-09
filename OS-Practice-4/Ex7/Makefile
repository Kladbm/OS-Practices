CC = gcc
CFLAGS = -Wall

all: environ

environ: environ.c environ_functions.c
	$(CC) $(CFLAGS) -o environ environ.c environ_functions.c

clean:
	rm -f environ

.PHONY: all clean
