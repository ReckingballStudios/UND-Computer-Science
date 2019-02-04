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

//Thou shall not disrespect the global variable, for it holds virtue and sovereignty   -MJR 2019
int desperate[3];

//Functions//

int writeFile(int *numEntries, char *(*words)){
    printf("writing words to file");
    FILE *word = fopen("words.txt", "w");

    int i;
    for(i = 0; i < *numEntries; i ++){
        fprintf(word, "%s\n", words[i]);
    }
    fclose(word);
    return 1;
}

int sortWords(int *numEntries, char *(*words)){
    int i, j;
    char rip[50];
    
    //YAY BUBBLE SORT... I LOVE O(n^2)!!!
    //Please note: This algorithm is literal Scheiße... It may take some time if you are using large files, lol
    for(i = 0; i < *numEntries; i ++){
        for(j = 0; j < *numEntries-i-1; j ++){
            
            if(strcasecmp(words[j+1], words[j]) <= 0){
                strcpy(rip, words[j]);
                strcpy(words[j], words[j+1]);
                strcpy(words[j+1], rip);
            }
        }
    }
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
    for(i = 0; i < 3; i ++){
        for(j = 0; j < desperate[i]; j ++){
            
            if(i == 0){
                words[j] = (char*)malloc(50 * sizeof(char));
			    fscanf(american0, "%s", words[j]);
                printf("%30s\t%p\n", words[j], &words[j]);
            } else if(i == 1){
                words[j + desperate[0]] = (char*)malloc(50 * sizeof(char));
                fscanf(american1, "%s", words[j + desperate[0]]);
                printf("%30s\t%p\n", words[j + desperate[0]], &words[j + desperate[0]]);
            } else if(i == 2){
                words[j + desperate[0] + desperate[1]] = (char*)malloc(50 * sizeof(char));
                fscanf(american2, "%s", words[j + desperate[0] + desperate[1]]);
                printf("%30s\t%p\n", words[j + desperate[0] + desperate[1]], &words[j + desperate[0] + desperate[1]]);
            }   
            
            //bug check
            k ++;
            if(k > *numEntries){goto exitst;}
        }
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
			
            *(*specEntries) += 1;
		}
        *(*specEntries) -= 1;
        if(i==0){desperate[0] = *(*specEntries);} 
        else if(i==1){desperate[1] = *(*specEntries);}
        else if(i==2){desperate[2] = *(*specEntries);}
        *numEntries += *(*specEntries);
        printf("Number of entries in american%d: %d , %p\n", i, *(*specEntries), *specEntries);
        if(i == 2){
            *specEntries -= 2 * sizeof(int*);   //Go back to original memory position
            break;
        }
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
        if(retrieveData(&numEntries, &specEntries, words) == 0){break;}

        printf("\n\n\n\nStage 3: Sorting Data\n");
        sortWords(&numEntries, words);

        printf("\n\n\n\nStage 4: Writing Data to File\n");
        //Write to a file, and save the file
        if(writeFile(&numEntries, words) == 0){break;}

        free(specEntries);
        free(words);

        printf("Continue? (1/0): \n");
	    scanf("%d", &numEntries);
        if(/*numEntries == 0*/1){break;}    
	}
    return 0;
}
