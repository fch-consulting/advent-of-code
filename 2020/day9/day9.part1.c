#include<stdio.h>
#include<stdlib.h>
#define STEP 25

int check(int *inputs, int inputs_size, int number);

int
main(){
	FILE *file;
	file = fopen("day9.input.full", "r");
	
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

	int next = STEP;
	int start = 0;

	int result = 0;
	for(int i=STEP; i<inputs_size-1; i++){
		int current = inputs[i];
		int t = check(inputs+(i-STEP), STEP, current);
		if(t==-1){
			result = current;
			break;
		}
	}

	printf("result: %d\n",result);
}

int check(int *inputs, int inputs_size, int number){

	for(int i=0; i < inputs_size; i++){
		for(int j = i+1; j <= inputs_size; j++){
			if(inputs[i]+inputs[j] == number){
				return 1;
			}
		}
	}

	return -1;
}
