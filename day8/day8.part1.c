#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct instruction {
	char *operation;
	signed int argument;
};

void print_instruction(struct instruction *input);
struct instruction *build_instruction(char *input);
void solve_part1(struct instruction **instructions, size_t inst_length);
int used_index(signed int previous[1000], size_t index);

int main(){
	printf("--------------\n");
	printf("starting day 8\n");
	printf("--------------\n");

	FILE *file;
	file = fopen("day8.input.full", "r");

	if(file == NULL){
		exit(EXIT_FAILURE);
	}

	char *current = malloc(10);
	struct instruction **instructions = NULL;
	size_t size_file = 0;
	
	while(fgets(current, 10, file)){
		current[strlen(current) - 1] = '\0';
		
		struct instruction **_instructions = realloc(instructions, (size_file+1) * sizeof(struct instruction*));
		if(_instructions == NULL){
			exit(EXIT_FAILURE);
		}
		instructions = NULL;
		instructions = _instructions;

		struct instruction *new_instruction = build_instruction(current);
		instructions[size_file] = new_instruction;

		size_file++;
	}

//	for(int i=0; i<size_file;i++){
//		print_instruction(instructions[i]);
//	}

	solve_part1(instructions, size_file);

	// free

	free(current);
	fclose(file);

	for(int i=0; i< size_file; i++){
		free(instructions[i]->operation);
		free(instructions[i]);
	}

	free(instructions);
}

void solve_part1(struct instruction **instructions, size_t inst_length){
	printf("------\n");
	printf("part 1\n");
	printf("------\n\n");


	signed int previous[1000] = {[0 ... 999]=-1};

	size_t index = 0;
	size_t i = 0;
	size_t acc = 0;

	while(i < inst_length){
		printf("--------------------\n");
		struct instruction *current = instructions[i];

		print_instruction(current);
		printf("checking{i: %ld}\n", i);

		if(used_index(previous, i)==1){
			break;
		}

		previous[index] = i;

		printf("index=%ld: %ld is not used\n", index, i);

		if(strcmp(current->operation, "nop")==0){
			i++;
		} else if (strcmp(current->operation, "acc")==0){
			acc += current->argument;
			printf("acc: %ld\n", acc);
			i++;
		} else if (strcmp(current->operation, "jmp")==0){
			i += current->argument;
		} else {
			printf("failure");
			exit(EXIT_FAILURE);
		}

		index ++;
	}

	printf("\n");
	printf("acc: %ld\n", acc);
	
}

int used_index(signed int previous[1000], size_t index){
	for(int i = 0; i<100; i++){

		if(previous[i] == index){
			return 1;
		}
	}

	return -1;
}

void print_instruction(struct instruction *input){
	printf("{operation:%s, argument: %d}\n", input->operation, input->argument);
}

struct instruction *build_instruction(char *input){
	char *_operation = malloc(4*sizeof(char));
	memset(_operation, '\0', 4);
	strncpy(_operation, input, 3);

	strtok(input, " ");
	char *next = strtok(NULL, " ");
	signed int _argument = atoi(next);

	struct instruction *new_instruction = malloc(sizeof(struct instruction));
	new_instruction->operation = _operation;
	new_instruction->argument = _argument;
	return new_instruction;
}
