#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>

#include "cvector/cvector.h"
#include "estring/estring.h"

struct termios orig_termios;

void init_terminal(void) {
	setvbuf(stdin, NULL, _IONBF, 0); // disable line buffering on stdin
	tcgetattr(STDIN_FILENO, &orig_termios);
	struct termios raw_termios = orig_termios;
	cfmakeraw(&raw_termios);
	tcsetattr(STDIN_FILENO, TCSANOW, &raw_termios);
}

void restore_terminal(void) {
	tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}

void exit_program(void) {
	restore_terminal();
	exit(0);
}

void handle_keypress(void) {
	int c = getchar();
	
	switch (c) {
	case 0x11: // Ctrl+Q
		exit_program();
		break;
	default: // do nothing
	}
}

// If this fails, errno should be set to whatever caused the error
Vec *load_file(const char *pathname) {
	// Open file descriptor and mmap
	int fd = open(pathname, O_RDONLY | O_CREAT);
	if (fd == -1) return NULL;
	
	struct stat file_stat;
	if (fstat(fd, &file_stat) == -1) return NULL;
	
	char *text = mmap(NULL, file_stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	close(fd);
	if (text == NULL) return NULL;
	
	// Initialize string push each line into a Vec.
	StringView str = {
		.data = text,
		.len = file_stat.st_size
	};
	
	Vec *lines = Vec(String);
	if (lines == NULL) return NULL;
	
	while (str.len > 0) {
		StringView tmp = StringView_tokenize(&str, "\n");
		tmp = String(tmp);
		Vec_push(lines, &tmp);
	}
	
	munmap(text, file_stat.st_size);
	return lines;
}

void print_text(Vec *lines) {
	String *lines_array = lines->data;
	for (size_t i = 0; i < lines->len; ++i) {
		printf("%s\r\n", String_to_cstr(lines_array[i]));
	}
}

void String_freeptr(void *str) {
	String_free(*(String *)str);
}

int main(int argc, char **argv) {
	Vec *lines;

	if (argc > 1) {
		const char *pathname = argv[1];
		lines = load_file(pathname);
	} else {
		lines = Vec(String);
		String str = String("");
		Vec_push(lines, &str);
	}
	
	init_terminal();
	print_text(lines);
	
	while (1) {
		handle_keypress();
	}
	
	restore_terminal();
	Vec_destroy(lines, &String_freeptr);
	return 0;
}
