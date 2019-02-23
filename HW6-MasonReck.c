/*
Mason Reck
CSCI 230
HW6
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

#include "HW6-A-MasonReck.h"
#include "HW6-B-MasonReck.h"
#include "HW6-C-MasonReck.h"
#include "HW6-D-MasonReck.h"


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
	blackbox = LOAD(&dataFile, fileSize);


	//Phase 3: Searching
	for(int z = 1; z < argc; z++)
		SEARCH(blackbox, *(argv + z), fileSize);
	

	//Phase 4: Freeing
	FREE(blackbox, fileSize);


	fclose(dataFile);
}
