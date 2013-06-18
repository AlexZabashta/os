#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h>
#include "nextString.h"

int main(int argc, char** argv) {
	struct StreamReader s;
	s.fd = 0;
	s.buffer = malloc(7);
	s.size = 6;
	s.l = s.len = 0;

	while(1) {
		int state = next(&s, '_');
		printf("%d : [%d  %d]", state, (int)s.l, (int)s.r);

		size_t t = 0;
		for (t = s.l; t <= s.r; t++) {
			printf("%c", s.buffer[t]);		
		}
		printf("\n");
		if (state == 3) {
			return 0;
		} else if (state == 1) {
			s.l = s.r + 1;
		}
	}
	return 0;
}
