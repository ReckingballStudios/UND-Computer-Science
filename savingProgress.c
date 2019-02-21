struct data *LOAD(FILE *stream, int size){
//Rewind file, create the dynamic array and read data
	stream = fopen("HW5.data", "r");
	struct data *blackbox;


	printf("  ...Loading Data...\n");
	blackbox = (struct data*)calloc(size + 1, sizeof(struct data));
	for(int i = 0; i < size + 1; i ++){
		blackbox[i].name = (char*)malloc(100 * sizeof(char));
		if(i == 0){continue;}
		fscanf(stream, "%s", blackbox[i].name);
		fscanf(stream, "%ld", &blackbox[i].number);
		//printf("\t%s %ld\n", blackbox[i].name, blackbox[i].number);
	}

	
	return blackbox;
}
