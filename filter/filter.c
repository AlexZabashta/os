#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


char *buffer;

int i;
int n;
char **ar;
int ac;
int eo = 0;
int len = 0;
int isEnd = 0;
int offset = 0;
int bufferSize = 4096;

void printBuffer (int finish) {
    buffer[finish - 1] = '\0';    
    ar[ac - 1] = buffer + offset;
    if(!fork()) {
        execv(ar[eo], ar + eo);
    }    
}

int main (int argc, char **argv) {
    int opt = 0;
    char sep = 'q';
    ar = argv;
    ac = argc;
    while((opt = getopt(argc, argv, "nzb:")) != -1) {
        switch(opt) {
            case 'n':
                if (sep == 'q')    {
                    sep = '\n';
                } else {
                    return 1;
                }
                break;
            case 'z':
                if (sep == 'q') {
                    sep = '\0';
                } else {
                    return 1;
                }
                break;
            case 'b':
                bufferSize = atoi(optarg);
                break;
            case '?':
            default:
                   return 1;    
        }    
    }
    
    for(i = 1; i < argc; i++) {
        if (*(argv[i]) == '-' && *(argv[i] + 1) == 'b' ) {
            continue;
        }
        if (*(argv[i]) == '-' && *(argv[i] + 1) == 'z' ) {
            continue;
        }
        if (*(argv[i]) == '-' && *(argv[i] + 1) == 'n' ) {
            continue;
        }
        if (*(argv[i]) < 58 && *(argv[i]) > 47 ) {
            continue;
        }    
        eo = i - 1;
        break;
    }    
    for (i = eo; i < argc - 1; i++) {
        argv[i] = argv[i + 1];
    }

    if (sep == 'q') {
        sep = '\n';
    }
    if (bufferSize <= 0) {
        return 1;
    }

    bufferSize++;    
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

        for (i = 0; i < len; i++) {
            if (buffer[i] == sep) {
                printBuffer(i + 1);
                offset = i + 1;                
            }
        }
        if (offset != 0 || isEnd) {
            if (isEnd && offset != len) {
                printBuffer(len);
            }
            memmove(buffer, buffer + offset, len - offset);            
            offset = len - offset;
        } else {
            return 1;
        }
        if (isEnd) {
            break;
        }
    }
    
    return 0;
}
