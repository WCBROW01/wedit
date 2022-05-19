CC=cc
CFLAGS=-Wall -Wextra -g

SRC=$(wildcard *.c cvector/*.c estring/*.c)
OBJ=$(SRC:.c=.o)

wedit: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(OBJ)
