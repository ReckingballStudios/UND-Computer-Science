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
int writeFile(int *numEntries, char *(*(*words))){
    printf("writing words to file");
    FILE *word = fopen("words.txt", "w");

    int i;
    for(i = 0; i < *numEntries; i ++){
        fprintf(word, "%s", *(*words));
        *(*words) += sizeof(char*) * 50;
    }
    fclose(word);
    return 1;
}

int retrieveData(int *numEntries, int *(*specEntries), char *(*words)){
    FILE *american0 = fopen("american0.txt", "r");
	FILE *american1 = fopen("american1.txt", "r");
	FILE *american2 = fopen("american2.txt", "r");
	if(american0 == NULL || american1 == NULL || american2 == NULL){
		//Exit the file open attempt
		printf("File was not found.\n");
		return 0;
	}
    
    
    int i, j, k = 0;
    int spec0 = 0, spec1 = 0;
    for(i = 0; i < 3; i ++){
        for(j = 0; j < *(*specEntries); j ++){
            if(i == 0){
                words[j] = (char*)malloc(50 * sizeof(char));
			    fscanf(american0, "%s", words[j]);
                printf("%30s\t%p\n", words[j], &words[j]);
            } else if(i == 1){
                words[j + spec0] = (char*)malloc(50 * sizeof(char));
                fscanf(american1, "%s", words[j + spec0]);
                printf("%30s\t%p\n", words[j + spec0], &words[j + spec0]);
            } else if(i == 2){
                words[j + spec0 + spec1] = (char*)malloc(50 * sizeof(char));
                fscanf(american2, "%s", words[j + spec0 + spec1]);
                printf("%30s\t%p\n", words[j + spec0 + spec1], &words[j + spec0 + spec1]);
            }   
            
            k ++;
            if(k > *numEntries){goto exitst;}
            //*words += sizeof(char*);
        }
        if(i == 2){
            *specEntries -= 2 * sizeof(int*);   //Go back to original memory position
            printf("Reading finished\n Reverting specEntries to %p\n", *specEntries);
            //*words -= *numEntries * sizeof(char**); 
            //printf("Reverting words (**) %p\n", *(*words));
        break;} else if(i == 0){
            spec0 = *(*specEntries);
        }   else if(i == 1){
            spec1 = *(*specEntries);
        }
        *specEntries += sizeof(int*); //next location in memory
    }
    exitst:
    fclose(american0);
    fclose(american1);
    fclose(american2);
    return 1;
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
            printf("Reverting specEntries to %p\n", *specEntries);
        break;}
        *specEntries += sizeof(int*); //next location in memory
       
	}

    printf("Total Entries: %d\n", *numEntries);

    fclose(american0);
    fclose(american1);
    fclose(american2);
    return 1;
}


int main (void) {

    int numEntries = 0;
    int *specEntries;
    specEntries = (int*)calloc(3, sizeof(int));
    char **words;
    int i = 0;
    
	while(1){
     
        printf("\nStage 1: Retrieving Files\n");
        //Retrieve the files, and retrieve file sizes
		if(retrieveFiles(&numEntries, &specEntries) == 0){break;}
        
        printf("\n\n\n\nStage 2: Retrieving Data\n");
        //Prep to receive the data and assign it to the dynamic array
        words = (char**)malloc((numEntries + 1) * sizeof(char*));
        /*for(i = 0; i < numEntries; i ++){
            *words = (char*)calloc(50, sizeof(char));
        }*/
        if(retrieveData(&numEntries, &specEntries, words) == 0){break;}




        printf("\n\n\n\nStage 4: Writing Data to File\n");
        //Write to a file, and save the file
        if(writeFile(&numEntries, &words) == 0){break;}

        free(specEntries);
        free(words);

        printf("Continue? (1/0): \n");
	    scanf("%d", &numEntries);
        if(numEntries == 0){break;}    
	}

    
    return 0;
}
