/*
Mason Reck
CSCI 230
HW6-C
2/19/2019
mason.reck@und.edu
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>


void SEARCH(struct data *blackbox, char *name, int size){
	//Find the name we are looking for, and the size of the array.

	//printf("  ...Searching Data...\n");
	struct data tempStruct;
	
	for(int j = 1; j < size + 1; j ++){
		//tempStruct = *(blackbox + j);	
		
		//printf("%s, %s\t%p\n", name, blackbox[j].name, &blackbox[j].name);
		if(strcmp(name, blackbox[j].name) == 0){
			printf("\n __________________________________________________________\n");
			printf("|%s was found at entry %5d |\n", name, j);
			printf(" ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n");
			goto exitfunction;
		}
	}
	printf("\n%s was NOT found. ¯\\_(ツ)_/¯\n", name);

	exitfunction:
	printf("\n");
}
