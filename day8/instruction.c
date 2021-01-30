#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<instruction.h>

struct instruction **copy_inst(struct instruction **input, size_t size){
	struct instruction **result = malloc(size * sizeof(struct instruction *));
	for(size_t i = 0; i < size; i ++){
		struct instruction *tmp = malloc(sizeof(struct instruction));
		char *_operation = malloc(4);
		memset(_operation, 4, '\0');
		strcpy(_operation, input[i]->operation);
		tmp->operation = _operation;
		tmp->argument = input[i]->argument;

		result[i] = tmp;
	}

	return result;
}

void free_instructions(struct instruction **instructions, size_t size){
	for(int i=0; i < size; i++){
		free(instructions[i]->operation);
		free(instructions[i]);
	}
	free(instructions);
}

struct instruction **nop_jmp(struct instruction **instructions, size_t size, size_t next){
	for(int i = 0; i < size; i++){
		if(strcmp(instructions[i]->operation, "nop")==0){
			if(next == 0){
				strcpy(instructions[i]->operation,"jmp");
				return instructions;
			} else {
				next --;
			}
		} else if (strcmp(instructions[i]->operation, "jmp")==0){
			if(next == 0){
				strcpy(instructions[i]->operation, "nop");
				return instructions;
			} else {
				next --;
			}
		}
	}
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
