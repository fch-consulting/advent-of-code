#include<stdio.h>
#include<stdlib.h>
#define STEP 25

struct result_struct{
	int *result;
	int result_size;
};

int check(int *inputs, int inputs_size, int number);
struct result_struct * check2(int *inputs, int input_size, int number);
void swap(int* xp, int* yp);
void selectionSort(int *input, int n);

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

	struct result_struct *r2 = NULL;
	for(int i=STEP; i<inputs_size-1; i++){
		int current = inputs[i];
		int t = check(inputs+(i-STEP), STEP, current);
		if(t==-1){
			r2 = check2(inputs, i, current);
			break;
		}
	}

	long int result;
	if(r2!=NULL){
		selectionSort(r2->result, r2->result_size);
		result = r2->result[0] + r2->result[r2->result_size - 1];
	}

	printf("result: %ld\n", result);
}

void swap(int* xp, int* yp) 
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
  
void selectionSort(int *input, int n) 
{ 
    int i, j, min_idx; 
  
    for (i = 0; i < n - 1; i++) { 
  
        min_idx = i; 
		for (j = i + 1; j < n; j++){
			if (input[j] < input[min_idx]){
				min_idx = j; 
			}
		}
  
        swap(&input[min_idx], &input[i]); 
    } 
} 

struct result_struct * check2(int *inputs, int input_size, int number){

	long int sum = 0;
	for(int i = 0; i < input_size - 1; i++){
		sum = inputs[i];
		for(int j=i+1; j < input_size; j++){
			sum = sum + inputs[j];
			if(sum == number){
				int first_index = i;
				int last_index = j;
				int result_size = ( j - i ) + 1;
				int *result_array = malloc(result_size * sizeof(int));
				for(int k = 0; k < result_size; k++){
					result_array[k] = inputs[i+k];
				}
				struct result_struct *result = malloc(sizeof(struct result_struct *));
				result->result_size = result_size;
				result->result = result_array;
				return result;
			} else if (sum > number){
				break;
			}
		}
	}

	return NULL;
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
