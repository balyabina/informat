#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>

#define BUF_SIZE 16

char* read_buf(int fd) {

	char* buffer = (char*)malloc(BUF_SIZE * sizeof(char));
	char* result_str = NULL;
	int readed = 0;
	while((readed = read(fd, buffer, BUF_SIZE)) > 0) {
		if (result_str == NULL) {
			result_str = (char*)calloc(readed + sizeof(char), 1);   //Attaching memory for argv[1] elements
		}
		else {
			result_str = realloc(result_str, (strlen(result_str) + 1) * sizeof(char) + readed);   // Attaching new memory for one more matrix
		}
		strncat(result_str, buffer, readed);   // Attach first readed number of buffer to result_str
	}

	if (readed < 0) {
		printf("Can't read string\n");
		exit(-1);
	}

	free(buffer);

	return result_str;
}

void write_buf(char* str, int fd) {

	int i;
	for(i = 0; i < strlen(str); i++) {
		if (write(fd, str + i, 1) < 0) {
			printf("Can't write a symbol\n");
			exit(-1);
		}
	}

	return;
}
