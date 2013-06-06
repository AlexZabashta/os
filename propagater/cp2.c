#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char** argv)
{
	if (argc < 2) {		
		return 1;
	}
	char** command = (char**) malloc((argc + 2) * sizeof(char*));
	int in, out, i;
	command[0] = (char*) malloc(16);
	sprintf(command[0], "%s", "./propagater");

	for (i = 1; i < argc; i += 2) {
		command[i] = (char*) malloc(10);
		command[i + 1] = (char*) malloc(10);
		in = open(argv[i], O_RDONLY);
		out = open(argv[i + 1], O_WRONLY | O_CREAT, 0644);
		sprintf(command[i], "%d", in);
		sprintf(command[i + 1], "%d", out);
	}
   
	execvp(command[0], command);
	free(command);
	return 0;
}
