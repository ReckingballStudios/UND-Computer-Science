/*
Mason Reck
CSCI 230
HW6-B C File
2/19/2019
mason.reck@und.edu
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct data{
	char *name;
	long number;
};

struct data *LOAD(FILE *(*stream), int size){
//Rewind file, create the dynamic array and read data
	//printf("  ...Loading Data...\n");
	//stream = fopen("hw5.data", "r");
	struct data *blackbox;

	char *line = NULL;
	size_t len = 0;	
		
	blackbox = (struct data*)calloc(size + 1, sizeof(struct data));
	
	rewind(*stream);

	for(int g = 1; g < size + 1; g ++){
		getline(&line, &len, *stream);
		line = strtok(line," ,\n");
		//printf("line length: %s, %zu\n", line, strlen(line));
		blackbox[g].name = (char*)calloc((int)strlen(line), sizeof(char));
		strncpy(blackbox[g].name, line, (int)strlen(line));
		line = strtok(NULL," ");
		blackbox[g].number = atol(line);
	} 
	

	return blackbox;
}
