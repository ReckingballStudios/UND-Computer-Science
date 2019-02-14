/*
Mason Reck
02/06/2019
Homework 4
CSCI 230
mason.reck@und.edu
*/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Functions//

char* vectorCreation(char *(*input)){
	*input = (char*)malloc(sizeof(char));
}

char* vectorAddition(char *input, int numInputs){
    //char *temp;
	input = (char*)calloc(numInputs, sizeof(char));
	return input;
}

int vectorPrint(char *(*input), int numInputs, char *(*original), char *(*second)){
	
		printf("\n\n");
        *input = *original;   //Setting the pointer to the original memory position
    	
        for(int i = 0; i < numInputs; i ++){
            printf("%2d: %c\t%p\n", i, *(*input), *input);
            if(i == 0){*input = *second + 1; continue;}
            *input += 0x21; 
            if(i >= 25){*input += 0x10;}
            if(i >= 41){*input += 0x10;}
            
        }
        
        printf("\n");
}



int main(void){

	char *input;
	int numInputs = 0;
    char helping = '`';
    vectorCreation(&input);
    char *original;
    char *second;
    original = input;
    printf("First memory location is: %p\n\n", original);

	do{
		printf("Please enter characters(ENTER when finished): \n ");
        do{
            if(numInputs == 1){second = input;}

		    input[numInputs] = getchar();
            printf(" %c\t%p\n", input[numInputs], &input[numInputs]);
                        //printf(" %c\t\n", input[numInputs]);
            
            if(input[numInputs] == '\n'){
            	input = vectorAddition(input, numInputs);
            	//Appending \0 to make it a string
            	input[numInputs + 1] = '\0';
            	break;
            }
            
            helping = input[numInputs];
		    numInputs ++;
            
            input = vectorAddition(input, numInputs);
        } while(helping != '\n');  
        
		vectorPrint(&input, numInputs, &original, &second);
		//for(int i = 0; i < numInputs; i ++){
		//	printf("%2d: %c\t%p\n", i, input[i], input);
		//}
		
		printf("\n\n");
		//char *hw4;
		//hw4 = "HW 4 input: ";
		char hw4Initial [13] = {'H', 'W', ' ', '4', ' ', 'I', 'n', 'p', 'u', 't', ':', ' ', '\0'};
		//printf("%s\n", hw4Initial);
		char *hw4;
		hw4 = (char*)malloc((13 + numInputs) * sizeof(char));
		strcpy(hw4, hw4Initial);
		//input = vectorAddition(&input, numInputs + 13);
		//printf("input: %s\n", input);
		//strcat(hw4, input);
		
		input = original;   //Setting the pointer to the original memory position
    	char *cat;
    	cat = (char*)calloc(numInputs, sizeof(char));
        for(int i = 0; i < numInputs; i ++){
        	cat[i] = *input;
            if(i == 0){input = second + 1; continue;}
            input += 0x21; 
            //if(i >= 25){*input += 0x10;}
            //if(i >= 41){*input += 0x10;}
        }
        strcat(hw4, cat);
        free(cat);
		printf("%s\n\n\n", hw4);
		free(hw4);
		
		
        printf("Enter 0 to exit or any character to continue.\n");
        char e;
        scanf("%c", &e);
        
        if(e == '0' || e == 32){break;}
        //free(input);
	} while(helping != '0' && helping != 32);
	
    free(input);
    
    
    return 0;
}




