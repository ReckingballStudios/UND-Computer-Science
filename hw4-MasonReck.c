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

int vectorCreation(char *(*input)){
	*input = (char*)malloc(sizeof(char));
}

int* vectorAddition(char *(*input), int numInputs){
    char *temp;
	*input = (char*)calloc(numInputs, sizeof(char));
}

int vectorRead(char *(*input), int numInputs){
    
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
		printf("Please enter characters(add a SPACE to finish): \n ");
        do{
            if(numInputs == 1){second = input;}

		    input[numInputs] = getchar();
            printf(" %c\t%p\n", input[numInputs], input);
            helping = input[numInputs];
		    numInputs ++;
            input += sizeof(char);
            vectorAddition(&input, numInputs);
        } while(helping != 32);  //32 is ascii code for space... if it is a space it will exit
        printf("\n\n");
        input = original;   //Setting the pointer to the original memory position


        //FIXME change to method
        for(int i = 0; i < numInputs; i ++){
            printf("%2d: %c in memory %p.\n", i, *input, input);
            if(i == 0){input = second; continue;}
            input += 32;    //20 hexidecimal translated to 32 decimal
        }
        
        printf("Enter 0 or any character to continue.\n");
        scanf("%c", &helping);
        scanf("%c", &helping);
	} while(helping != '0');
	
    exit:

    free(input);
    return 0;
}




