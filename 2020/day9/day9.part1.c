#include<stdio.h>
#include<stdlib.h>
#define STEP 5

int
main(){
	FILE *file;
	file = fopen("day9.input.test", "r");
	
	if(file == NULL){
		exit(EXIT_FAILURE);
	}

	int *inputs = NULL;
	int inputs_size = 0;
	int tmp;

	while(fscanf(file, "%d", &tmp)!=EOF){
		int *_inputs = realloc(inputs, sizeof(int) * (inputs_size+1));
		if(_inputs == NULL){
			exit(EXIT_FAILURE);
		}
		inputs = NULL;
		inputs = _inputs;
		inputs[inputs_size] = tmp;
		inputs_size++;
	}

	for(int i=0; i<inputs_size; i++){
		printf("%d\n", inputs[i]);
	}

	printf("-----------------------\n");

	int next = STEP;
	int start = 0;
}

int check(int *inputs, int input_size, int number){

	for(int i=0; i < inputs_size; i++){
		for(int j = i+1; j < inputs_size; j++){
			if(i+j == number){
				return 1;
			}
		}
	}

	return -1;
}
