#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h>

struct StreamReader {
	int fd;
	char* buffer;
	size_t size, len, l, r;
};

int next(struct StreamReader *s, char sep) {
	int t = s->l;
	while(1) {
		for (s->r = t; s->r < s->len; s->r++) {
			if(s->buffer[s->r] == sep) {
				return 1;
			}
		}
	}
	return s->fd;
}
