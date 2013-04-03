#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int bufferSize = 0;
	void *buffer;	
	
	while (*(argv[1]) != '\0')
	{
		bufferSize *= 10;
		bufferSize += *((argv[1])++) - '0';
	}
	
	buffer = malloc(sizeof(char) * bufferSize);
	
	read(0, buffer, bufferSize);
	write(1, buffer, bufferSize);	
	return 0;
	
}
