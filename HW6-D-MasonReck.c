/*
Mason Reck
CSCI 230
HW6-D C File
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

void FREE(struct data *blackbox, int size){
//Free all dynamically allocated memory.
	//printf("  ...Freeing Memory...\n");
	for(int k = 1; k < size + 1; k ++){
		//printf("Freeing %s\t%p\n", blackbox[k].name, &blackbox[k].name);
		free(blackbox[k].name);
	}
			
	free(blackbox);
}

