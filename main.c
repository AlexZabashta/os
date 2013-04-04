#include <stdio.h>
#include <stdlib.h>

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
	while (*(argv[1]) != '\0') {
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
		searchNewLines();
		if (isOverFlow) 
		{
			for (i = 0; i < len; i++)
			{
				
			}
		}
		else
		{
			
		}
		
		if (len < bufferSize)
		{
			break;
		}
	}
	return 0;
}
