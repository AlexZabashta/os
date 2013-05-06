#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char *buffer;

int i;
int n;
int len = 0;
int isEnd = 0;
int offset = 0;
int isOverFlow = 0;
int bufferSize = 0;

void printBuffer (int finish) {
	write(1, buffer + offset, finish - offset);
	write(1, buffer + offset, finish - offset);
}

int main (int argc, char **argv) {	
	while (*(argv[1]) != '\0')
	{
		bufferSize *= 10;
		bufferSize += *((argv[1])++) - '0';
	}
	bufferSize++;
	buffer = malloc(sizeof(char) * bufferSize);	
	
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
					printBuffer(i + 1);
					offset = i + 1;
				}
			}
		}
		if (offset != 0 || isEnd) {
			if (isEnd) {
				printBuffer(len);
			}
			memmove(buffer, buffer + offset, len - offset);			
			offset = len - offset;
		} else {
			isOverFlow = 1;
		}
		if (isEnd) {
			break;
		}
	}
	
	return 0;
}
