/*
Mason Reck
Homework 5
CSCI 230
02/12/2019
mason.reck@und.edu
*/


#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//Global Struct//
struct data{
	char *name;
	long number;
};
int *llength;

//Functions//
int SCAN(FILE *(*stream)){
//Open the file and return an integer indicating how many lines there are.
	printf("  ...Scanning Data...\n");
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

struct data *LOAD(FILE *stream, int size){
//Rewind file, create the dynamic array and read data
	stream = fopen("HW5.data", "r");
	struct data *blackbox;


	printf("  ...Loading Data...\n");
	blackbox = (struct data*)malloc(size + 1);
	for(int i = 0; i < size + 1; i ++){
		blackbox[i].name = (char*)malloc(100 * sizeof(char));
		if(i == 0){continue;}
		fscanf(stream, "%s", blackbox[i].name);
		fscanf(stream, "%ld", &blackbox[i].number);
		//printf("\t%s %ld\n", blackbox[i].name, blackbox[i].number);
	}
	
	return blackbox;
}

void SEARCH(struct data *blackbox, char *name, int size){
//Find the name we are looking for, and the size of the array.

	printf("  ...Searching Data...\n");
	struct data tempStruct;
	
	for(int j = 1; j < size + 1; j ++){
		//tempStruct = *(blackbox + j);	
		
		//printf("%s, %s\n", name, blackbox[j].name);
		if(strcmp(name, blackbox[j].name) == 0){
			printf("\n __________________________________\n");
			printf("|The name was found at entry %5d |\n", j);
			printf(" ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n");
			goto exitfunction;
		}
	}
	printf("\n%s was NOT found. ¯\\_(ツ)_/¯\n", name);

	exitfunction:
	printf("\n");
}

void FREE(struct data *blackbox, int size){
//Free all dynamically allocated memory.
	for(int k = 0; k < size + 1; k ++)
			free(blackbox[k].name);

	free(blackbox);
}



int main(int argc, char *(*argv)){
	if(argc == 1){	//BUG catch
		printf("You MUST include a name to search for.\n");
		return 0;
	}

	//Phase 1: Scanning
	FILE *dataFile = fopen("HW5.data", "r");
	int fileSize = SCAN(&dataFile);
	

	//Phase 2: Loading
	struct data *blackbox;
	blackbox = LOAD(dataFile, fileSize);


	//Phase 3: Searching
	SEARCH(blackbox, *(argv + 1), fileSize);
	

	//Phase 4: Freeing
	//FREE(blackbox, fileSize);


	end:
	fclose(dataFile);
}

