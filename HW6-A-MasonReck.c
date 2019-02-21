/*
Mason Reck
CSCI 230
HW6-A C File
2/19/2019
mason.reck@und.edu
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>



int SCAN(FILE *(*stream)){
//Open the file and return an integer indicating how many lines there are.
	//printf("  ...Scanning Data...\n");
	char *line = NULL;
	size_t len = 0;	
	ssize_t read = 0;
	if(*stream == NULL)
		exit(EXIT_FAILURE);

	int fileSize = 0;
	while((read = getline(&line, &len, *stream)) != -1) {
		//printf("\t%s", line);
		fileSize ++;
	}
	free(line);

	return fileSize;
}
