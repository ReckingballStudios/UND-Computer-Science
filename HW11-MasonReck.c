/*
Mason Reck
CSCI 230 HW10
4/17/2019
mason.reck@und.edu
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Structure for linked list//
struct location{
	char *name;
	short numPaths;
	struct location **path;
	int *pathWeight;
	struct location *next;
};
typedef struct location loc;


//FUNCTIONS//

//Reads in the locations from the data file//
loc * readLocations(FILE *file){
	loc *head = NULL;
	head = (loc*) malloc(sizeof(loc));
	loc *cur = NULL;
	cur = (loc*) malloc(sizeof(loc));
	
	size_t len = 0;
	char *line = NULL;
	short first = 1; 
	while(getline(&line, &len, file) != -1){
		//Stop when finished with the first section of the data file
		if(strncasecmp(line, "STOP", 4) == 0){
			free(line);
			line = NULL;
			break;
		}
		
		cur->name = (char*) calloc(len, sizeof(char));
		strncpy(cur->name, line, strlen(line)-1);
		cur->next = (loc*) malloc(sizeof(loc));
		if(first == 1){
			head->name = (char*) calloc(len, sizeof(char));
			strncpy(head->name, line, strlen(line)-1);
			head->next = cur->next;
			first = 0;
		}
		
		cur = cur->next;
		free(line);
		line = NULL;
	}
	
	return head;
}

void printLocations(loc *cur){
	//printf("...Printing Locations...\n");
	while(cur->next){
		printf("%s\n", cur->name);

		
		for(int i = 0; i < cur->numPaths; i ++){
			printf("\t==> %s :: %d\n", cur->path[i]->name, cur->pathWeight[i]);
		}


		cur = cur->next;
	}
}

void allocatePaths(loc *cur){
	while(cur->next){
		cur->numPaths = 0;
		cur->path = (loc**) calloc(10, sizeof(loc*));
		for(int i = 0; i < 10; i ++)
			cur->path[i] = (loc*) calloc(1, sizeof(loc));

		cur->pathWeight = (int*) calloc(10, sizeof(int));
		cur = cur->next;
	}
}

int addPath(loc *head, char *start, char *finish, int weight){
	loc *cur = head;
	loc *end = head;
	while(cur->next){
		if(strncasecmp(start, cur->name, strlen(start)) == 0){
			//Start node found
			while(end->next){
				if(strncasecmp(finish, end->name, strlen(finish)) == 0){
					//Finish node found
					cur->path[cur->numPaths] = end;
					cur->pathWeight[cur->numPaths] = weight;
					cur->numPaths ++;
					return 1;
				}
				end = end->next;
			}
		}
		cur = cur->next;
	}
	return 0;
}

void readPaths(FILE *file, loc *head){
	//printf("\n...Reading in Paths...\n");
	//Variables for establishing the path
	char *start = NULL;
	char *finish = NULL;
	char *temp = NULL;
	int weight = 0;
	
	size_t len = 0;
	char *line = NULL;
	while(getline(&line, &len, file) != -1){
		if(strncasecmp(line, "STOP", 4) == 0){
			free(line);
			line = NULL;		
			break;
		}
		
		//Read in starting location
		temp = strtok(line, " ");
		start = (char*)calloc(strlen(temp), sizeof(char));
		strcpy(start, temp);

		//Read in finishing location
		temp = strtok(NULL, " ");
		finish = (char*)calloc(strlen(temp), sizeof(char));
		strcpy(finish, temp);

		//Read in weight (distance)
		temp = strtok(NULL, " ");
		weight = atoi(temp);
		
		//printf("%s %s %d\n", start, finish, weight);
		//Add the path to the linked list
		int success = addPath(head, start, finish, weight);
		//if(success == 1){printf("Node Addition Success: %s ==> %s :: %d\n", start, finish, weight);}
		if(success == 0){printf("Node Addition Failure\n");}	

		free(start);
		free(finish);
		free(line);
		start = NULL;
		finish = NULL;
		line = NULL;
	}
}

loc *readStart(FILE* file, loc *cur){
	//Read the last line in the file, the starting establishment
	size_t len = 0;
	char *line = NULL;
	char *start = NULL;

	getline(&line, &len, file);
	start = (char*) calloc(len, sizeof(char));
	strncpy(start, line, strlen(line)-1);

	while(cur->next){
		if(strncasecmp(start, cur->name, strlen(start)) == 0){
			//Starting Node Found!
			free(start);
			//printf("Starting Location is %s\n", cur->name);
			return cur;
		}
		cur = cur->next;
	}
	free(start);
	printf("Starting Location NOT Found!\n");
}

int drunkardsWalk(loc *start){
	printf("Please note that BAC = weight/cost\n");
	//Have the user enter a random seed
	int ran = 0;
	printf("Please enter a random seed: ");
	scanf("%d", &ran);
	srandom(ran);
	
	printf("\n...Starting to Drunkly Walk...\n");
	int weight = 0;
	int to = -1;
	loc *cur = start;

	while(strcasecmp(cur->name, "home") != 0){
		printf("location: %s\t::Total BAC: %d\n", cur->name, weight);
		if(cur->numPaths == 0){
			printf("There's no way home! D: And my BAC is %d!\n", weight);
			printf("I started at %s end ended up at %s\n", start->name, cur->name);
			return 0;
		}
		
		to = (int) (random() % cur->numPaths);
		weight += cur->pathWeight[to];
		cur = cur->path[to];
	}
	printf("I'm home! And my BAC is only %d!\n", weight);
	printf("I started at %s end ended up at %s\n", start->name, cur->name);
	return 1;
}

void FREE(loc *cur){
	//printf("\n...Freeing Memory...\n");
	loc *temp = NULL;
	while(cur->next){
		free(cur->name);
		free(cur->path);
		free(cur->pathWeight);
		temp = cur->next;
		free(cur);
		cur = temp;
	}
}


int main(void){
	FILE *file = fopen("./hw11.data", "r");
	
	loc *locations = NULL;
	loc *start = NULL;
	
	//STEP 1: Read in the locations!
 	locations = readLocations(file);
 	//printLocations(locations);
 	
 	//STEP 2: Establish the paths between locations
	allocatePaths(locations);
 	readPaths(file, locations);
	//printLocations(locations);

	//STEP 3: Start at the starting location
	start = readStart(file, locations);
	
	//STEP 4:Drunkard's walk
	int home = drunkardsWalk(start);


	FREE(locations);
	return EXIT_SUCCESS;
}

