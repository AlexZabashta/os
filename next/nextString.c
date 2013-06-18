#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h>
#include "nextString.h"

int main(int argc, char** argv) {
	struct StreamReader sr;
	sr.fd = 12345;
	int n = next(&sr, '\0');
	printf("%d\n", n);
	return 0;
}
