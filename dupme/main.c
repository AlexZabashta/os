#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


void printBuffer (char *buffer, int offset, int finish) {
	write(1, buffer + offset, finish - offset);
	write(1, buffer + offset, finish - offset);
}

int main (int argc, char **argv) {

	char *buffer;
	int i;
	int n;
	int len = 0;
	int isEnd = 0;
	int offset = 0;
	int isOverFlow = 0;

	if (argc < 2) {
		return 1;
	}

	int bufferSize = atoi(argv[1]) + 1;

	if ((buffer = malloc(bufferSize)) == NULL) {
		return 1;
	}
	
	while (1) {		
		len = offset;

		while (len < bufferSize) {
			n = read(0, buffer + len, bufferSize - len);
			if (n == 0) {
				isEnd = 1;
				break;
			}
			len += n;

		}
		offset = 0;

		for (i = offset; i < len; i++) {
			if (buffer[i] == '\n') {
				if (isOverFlow) {
					if (i + 1 != len) {
						offset = i + 1;
						isOverFlow = 0;
						break;
					}
					offset = len;

				} else {
					printBuffer(buffer, offset, i + 1);
					offset = i + 1;
				}
			}
		}
		if (offset != 0 || isEnd) {
			if (isEnd) {
				printBuffer(buffer, offset, len);
				break;
			}
			memmove(buffer, buffer + offset, len - offset);
			offset = len - offset;
		} else {
			isOverFlow = 1;
		}		
	}
	free(buffer);
	return 0;
}
