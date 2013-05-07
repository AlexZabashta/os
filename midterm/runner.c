#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

char *buffer;
char **stack;
int sp = 0;

int i, j;
int n;
int len = 0;
int isEnd = 0;
int offset = 0;
int bufferSize = 8192;
int fileOffset = 0;
int bufferOffset = 0;

void execLine(char *in, char *com, char **args, char *out) {    
    stack[sp - 1] = 0;
    sp = 0;
        
    if(!fork()) {
		int inFile = open (in, O_RDONLY);
		int outFile = open (out, O_WRONLY);
        dup2(inFile, 0);
        dup2(outFile, 1);    
        execv(com, args);        
        sleep(1);    
		close(outFile);
		close(inFile);
    }    
}

void execBuffer(int finish) {    
    if (finish - 1 == offset) {
        if (sp > 3) {
            execLine(stack[0], stack[1], &stack[2], stack[sp - 1]);        
        } else if (sp == 3) {
            execLine(stack[0], stack[1], 0, stack[sp - 1]);            
        } else {
            return;
        }
    } else {
        stack[sp] = buffer + offset;
        sp++;
    }
}

int main (int argc, char **argv) {

    buffer = malloc(sizeof(char) * bufferSize);
    stack = malloc(sizeof(char) * 4096);
    
    int inFile = open (argv [1], O_RDONLY);
    
    while (1) {        
        len = offset;

        while (len < bufferSize) {                        
            n =    read(inFile, buffer + len, bufferSize - len);
            if (n == 0) {
                isEnd = 1;
                break;
            }
            len += n;            
        }
        offset = 0;        
        for (i = 0; i < len; i++) {
            if (buffer[i] == '\0') {                
                execBuffer(i + 1);
                offset = i + 1;                
            }
        }
        if (offset != 0 || isEnd) {
            if (isEnd && offset != len) {
                execBuffer(len);                
            }
            memmove(buffer, buffer + offset, len - offset);            
            offset = len - offset;
        } else {
            return 1;
        }
        if (isEnd) {
            execBuffer(offset + 1);
            break;
        }
    }    
    close(inFile);
    free(buffer);
    free(stack);
}
