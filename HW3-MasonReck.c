/*
Mason Reck
CSCI 230
HW3
1/30/2019
mason.reck@und.edu
*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h> 
#include<string.h>


//Functions//
int retrieveData(int *numEntries, int *(*specEntries), char *(*words)){
    FILE *american0 = fopen("american0.txt", "r");
	FILE *american1 = fopen("american1.txt", "r");
	FILE *american2 = fopen("american2.txt", "r");
	if(american0 == NULL || american1 == NULL || american2 == NULL){
		//Exit the file open attempt
		printf("File was not found.\n");
		return 0;
	}
    
    
    int i;
    for(i = 0; i < *(*specEntries); i ++){
        
    }
    
}
                      
int retrieveFiles(int *numEntries, int *(*specEntries)){

	FILE *american0 = fopen("american0.txt", "r");
	FILE *american1 = fopen("american1.txt", "r");
	FILE *american2 = fopen("american2.txt", "r");
	if(american0 == NULL || american1 == NULL || american2 == NULL){
		//Exit the file open attempt
		printf("File was not found.\n");
		return 0;
	}

	
	char breakTest [50];
	int i;
	for(i = 0; i < 3; i++){
        *(*specEntries) = 0;
        char fileTest;
            if(i == 0){
			    fileTest = getc(american0);
            } else if(i == 1){
                fileTest = getc(american1);
            } else if(i == 2){
                fileTest = getc(american2);
            }
        
		while(fileTest != EOF){
            
            if(i == 0){
			    fscanf(american0, "%s", breakTest);
                fileTest = getc(american0);
            } else if(i == 1){
                fscanf(american1, "%s", breakTest);
                fileTest = getc(american1);
            } else if(i == 2){
                fscanf(american2, "%s", breakTest);
                fileTest = getc(american2);
            }    
            //printf("%s\n", breakTest);
			
            *(*specEntries) += 1;
		}
        *(*specEntries) -= 1;
        *numEntries += *(*specEntries);
        printf("Number of entries in american%d: %d , %p\n\n", i, *(*specEntries), *specEntries);
        if(i == 2){
            *specEntries -= 2 * sizeof(int*);   //Go back to original memory position
            printf("Reverting specEntries back to original address %p\n", *specEntries);
        break;}
        *specEntries += sizeof(int*); //next location in memory
       
	}
    //printf("test b4 total\n");
    printf("address: %p\n", &(*numEntries));
    printf("Total Entries(inMethod): %d\n", *numEntries);

    

}


int main (void) {

    int numEntries = 0;
    printf("address: %p\n", &(numEntries));
    int *specEntries;
    specEntries = (int*)calloc(3, sizeof(int));
    char *words;
    
	while(1){
     
		if(retrieveFiles(&numEntries, &specEntries) == 0){break;}
        printf("total Entries: %d\n", numEntries);
        words = (char*)calloc(numEntries, sizeof(char) * 50);
        scanf("%s", *words);    //FIXME delete
        if(retrieveData(&numEntries, &specEntries, &words) == 0){break;}
	
		FILE *word = fopen("words.txt", "w");

	}

    free(specEntries);
    free(words);
    return 0;
}
