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
		for(s->r = t; s->r < s->len; s->r++) {
			if(s->buffer[s->r] == sep) {
				return 1; // OK   l:[string + 'sep']:r
			}
		}
		if(s->len == s->size) {
			if(s->l == 0) {
				s->len = 0;
				s->r--;				
				return 2; // buffer overflow 0:[##### + c]:size => c != sep
			}
			memmove(s->buffer, s->buffer + s->l, s->len - s->l); // [####labcde] -> [labcde]
			s->len -= s->l;
			s->r -= s->l;
			s->l = 0;
		}
		size_t q = read(s->fd, s->buffer + s->len, s->size - s->len);
		if (q == 0) {
			s->r--;
			return 3; // end of stream
		}
		t = s->len;
		s->len += q;
		
	}
	return 3;
}
