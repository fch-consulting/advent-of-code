#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<day8.part2.h>

int main(){

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

	size_t next = 0;
	int result = -1;
	
	while(result == -1){
		struct instruction **new_instruction = copy_inst(instructions, size_file);
		nop_jmp(new_instruction, size_file, next);
		result = solve(new_instruction, size_file);

		if(result == -1){
			next++;	
		}

		if(next>size_file){
			exit(EXIT_FAILURE);
		}

		free_instructions(new_instruction, size_file);
	}


	free(current);
	fclose(file);

	free_instructions(instructions, size_file);

	printf("{result: %d}\n", result);
}

int solve(struct instruction **instructions, size_t inst_length){

	signed int previous[1000] = {[0 ... 999]=-1};

	size_t index = 0;
	size_t i = 0;
	int acc = 0;

	while(i < inst_length){
		struct instruction *current = instructions[i];

		if(used_index(previous, i)==1){
			return -1;
		}

		previous[index] = i;

		if(strcmp(current->operation, "nop")==0){
			i++;
		} else if (strcmp(current->operation, "acc")==0){
			acc += current->argument;
			i++;
		} else if (strcmp(current->operation, "jmp")==0){
			i += current->argument;
		} else {
			exit(EXIT_FAILURE);
		}

		index ++;
	}

	return acc;
}

int used_index(signed int previous[1000], size_t index){
	for(int i = 0; i<1000; i++){
		if(previous[i] == index){
			return 1;
		}
	}

	return -1;
}
