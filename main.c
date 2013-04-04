#include <stdio.h>
#include <stdlib.h>

char *buffer;
int bufferSize = 5;
int i;
int last = 0;
int isOverFlow = 0;
int len = 0;

void printBuffer (int start, int finish)
{
	write(1, buffer + start, finish - start);
	write(1, buffer + start, finish - start);
}

void searchNewLines()
{
	for (i = last; i < len; i++)
	{
		if (*(buffer + i) == '\n')
		{
			printBuffer(last, i + 1);
			last = i + 1;
			isOverFlow = 0;
		}
	}
	
}

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
		len = read(0, buffer + last, bufferSize);
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
