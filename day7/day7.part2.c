#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<bag.h>

struct inputs_struct *load_file(FILE *file);

struct inputs_struct {
	size_t file_size;
	char ** lines;
};

int
main(){
	FILE *file;
	file = fopen("day7.input.full", "r");
	if(file == NULL){
		exit(EXIT_FAILURE);
	}

	struct inputs_struct *inputs = load_file(file);

	// transform the inputs to a tree
	struct bag root = {1, "shiny gold", NULL, 0};
	build_bags_tree(&root, inputs->lines, inputs->file_size);
	print_bag(&root);

//	print_bags(&root);

	long unsigned int total_bags = qty(&root) - 1;

	printf("result = %ld\n", total_bags);


	// freeing memory
	for(int i=0; i<root.contains_size; i++){
		free(root.contains[i]->color);
		free(root.contains[i]);
	}

	free(root.contains);

	for(int i=0; i<inputs->file_size; i++){
		free(inputs->lines[i]);
	}

	free(inputs->lines);
	free(inputs);
}

struct inputs_struct *load_file(FILE *file){
	char *current = malloc(500);
	char **inputs=NULL;
	size_t index = 0;

	// extracting input to array of char *
	while(fgets(current, 500, file)!=NULL){
		current[strlen(current)-1]='\0';

		if(inputs==NULL){
			inputs=malloc(sizeof(char *));
			inputs[index] = malloc(strlen(current)+1);
			strcpy(inputs[index], current);
		} else {
			char **_inputs = realloc(inputs, (index + 1) * sizeof(char *));
			if(_inputs==NULL){
				exit(EXIT_FAILURE);
			}
			inputs = NULL;
			inputs = _inputs;
			inputs[index] = malloc(strlen(current) + 1);
			strcpy(inputs[index], current);
		}

		index++;
	}

	free(current);
	fclose(file);

	struct inputs_struct *result = malloc(sizeof(struct inputs_struct));
	result->lines = inputs;
	result->file_size = index;


	return result;
}
