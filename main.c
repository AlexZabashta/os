#include <stdio.h>
#include <stdlib.h>

char *buffer;
int bufferSize = 0;

int main (int argc, char **argv)
{	
	while (*(argv[1]) != '\0')
	{
		bufferSize *= 10;
		bufferSize += *((argv[1])++) - '0';
	}
	
	buffer = malloc(sizeof(char) * bufferSize);	
	
	while (1)
	{
		int len = read(0, buffer, bufferSize);
		write(1, buffer, len);
		putchar('\n');
		if (len < bufferSize)
		{
			break;
		}
	}
	
	return 0;
	
}

void printBuffer (int start, int finish)
{
	write(1, buffer + start, finish - start);
	write(1, buffer + start, finish - start);
}
