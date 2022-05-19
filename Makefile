CFLAGS=-Wall -Wextra -g

SRC=$(wildcard *.c cvector/*.c estring/*.c)
OBJ=$(SRC:.c=.o)

wedit: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -f $(OBJ)

.PHONY: build-deps
build-deps:
	git clone https://github.com/WCBROW01/cvector.git cvector
	git clone https://github.com/WCBROW01/enhanced-cstrings.git estring
	
.PHONY: clean-deps
clean-deps:
	rm -rf cvector estring
