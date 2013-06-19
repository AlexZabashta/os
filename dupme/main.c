#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "./../next/nextString.h"

int main (int argc, char **argv) {

	struct StreamReader s;
	s.fd = 0;
	s.l = s.len = 0;

	if (argc < 2) {
		return 1;
	}
	s.size = atoi(argv[1]) + 1;

	if ((s.buffer = malloc(s.size)) == NULL) {
		return 1;
	}

	int state = 0;	
	while (state != 3) {		
		int tempState = next(&s, '\n');
		if (tempState != 2 && state != 2 && s.l <= s.r)	{
			write(1, s.buffer + s.l, s.r - s.l);
			write(1, "\n", 1);
			write(1, s.buffer + s.l, s.r - s.l);
			write(1, "\n", 1);			
		}
		s.l = s.r + 1;
		state = tempState;
	}
	free(s.buffer);
	return 0;
}
