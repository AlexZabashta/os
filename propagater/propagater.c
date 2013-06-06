#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h>
#define _GNU_SOURCE 
#include <poll.h> 
 
int main (int argc, char **argv) {
	int i;
	int bufferSize = 4096;	
	char *buffer = malloc(bufferSize);
	if (buffer == NULL || argc == 1 || argc % 2 == 0) {
		return 1;
	}
	size_t pollSize = argc - 1;
	struct pollfd* pollArray = (struct pollfd*) malloc(pollSize * sizeof(struct pollfd));	
	if (pollArray == NULL) {
		free(buffer);		
		return 2;
	}
	
	for (i = 0; i < pollSize; i++) {
		int d = 0;
		while (*(argv[i + 1]) != '\0')	{
			d *= 10;
			d += *((argv[i + 1])++) - '0';
		}		
		pollArray[i].fd = d;
		pollArray[i].events = (i % 2 == 0 ? POLLIN : POLLOUT);		
	}	
	while(pollSize > 0) {
		int state = poll(pollArray, pollSize, 0);
		if (state == 0) {
			break;
		}
		if (state == -1) {
			free(buffer);
			free(pollArray);			
			return 3;
		}
			
		for (i = 0; i < pollSize; i += 2) {
			if ((pollArray[i].revents & POLLIN) > 0 && (pollArray[i + 1].revents & POLLOUT) > 0) {
				int len = read(pollArray[i].fd, buffer, bufferSize);
				if (len == 0) {					
					if (pollSize == 2 || i + 2 == pollSize) {
						i = pollSize;						
					} else {
						int tmp = pollArray[i].fd;
						pollArray[i].fd = pollArray[pollSize - 2].fd;
						pollArray[pollSize - 2].fd = tmp;
						tmp = pollArray[i + 1].fd;
						pollArray[i + 1].fd = pollArray[pollSize - 1].fd;
						pollArray[pollSize - 1].fd = tmp;
						i -= 2;
					}
					pollSize -= 2;
					continue;
				}
				write(pollArray[i + 1].fd, buffer, len);		
			} 
		}		
	
	}
	free(pollArray); 	
	free(buffer);
	return 0; 
} 
