#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<bag.h>


void build_bags_tree(struct bag* current, char **inputs, long unsigned int inputs_size){
	build_bag(current, inputs, inputs_size);
	for(int i = 0; i < current->contains_size; i++){
		build_bags_tree(current->contains[i], inputs, inputs_size);
	}
}

struct bag* build_bag(struct bag *current_bag, char **inputs, long unsigned int inputs_size){
	char *bag_color = current_bag->color;

	for(int i=0; i<inputs_size; i++){
		char *line = inputs[i];
		char *str  = strstr(line, "bag");

		int index = str - line - 1;

		char *color = malloc(index+1);
		memset(color, '\0', index + 1);
		strncpy(color, line, index);

		if(strcmp(color, bag_color)==0){
			char *sub = strstr(line, "contain");
			sub = sub + 8; // remove "contain "

			if(strstr(sub, "no other bags")!=NULL){
				current_bag->contains = NULL;
				free(color);
				return current_bag;
			} 

			// create subbags
			char *sub1 = strstr(sub, ",");
			if(sub1!=NULL){
				sub1 = sub1 + 2;
			}

			while(sub1){
				unsigned int index = sub1 - sub - 2; 
				char *number_str = &sub[0];
				int qty = atoi(number_str);

				char *tmp = malloc(index+1);
				memset(tmp, '\0', index + 1);
				strncpy(tmp, sub, index);
				char *tmp22 = tmp+2;
				char *tmp2 = strstr(tmp22, "bag");

				unsigned int index2 = tmp2 - tmp22 - 1;
				char *color = malloc(index2+1);
				memset(color, '\0', index2+ 1);
				strncpy(color, tmp22, index2);

				struct bag *_bag = malloc(sizeof(struct bag));;
				_bag->qty = qty;
				_bag->contains = NULL;
				_bag->color = color;
				_bag->contains_size=0;

				sub = sub1;// = sub1 + 2;
				sub1 = strstr(sub1, ",");
				if(sub1!=NULL){
					sub1 = sub1 + 2;
				}

				if(current_bag->contains_size == 0){
					current_bag->contains = malloc(sizeof(struct bag *));
					current_bag->contains[0] = _bag;
				} else {
					struct bag **_contains = realloc(current_bag->contains, (current_bag->contains_size + 1) * sizeof(struct bag *));
					if(_contains == NULL){
						exit(EXIT_FAILURE);
					}

					current_bag->contains = NULL;
					current_bag->contains = _contains;
					current_bag->contains[current_bag->contains_size] = _bag;
				}

				current_bag->contains_size++;

				free(tmp);
			}

			char number_str = sub[0];
			int qty = atoi(&number_str);

			int index = strstr(sub, "bag") - 1 - (sub + 2);

			char *tmp = malloc(index + 1);
			memset(tmp, '\0', index+1);
			strncpy(tmp, sub + 2, index);

			struct bag *_bag = malloc(sizeof(struct bag));;
			_bag->qty = qty;
			_bag->contains = NULL;
			_bag->color = tmp;
			_bag->contains_size=0;

			if(current_bag->contains_size == 0){
				current_bag->contains = malloc(sizeof(struct bag *));
				current_bag->contains[current_bag->contains_size] = _bag;
			} else {
				size_t next_size = ((current_bag->contains_size)+1) * sizeof(struct bag *);
				struct bag **_contains = realloc(current_bag->contains, next_size);

				if(_contains == NULL){
					exit(EXIT_FAILURE);
				}

				current_bag->contains = NULL;
				current_bag->contains = _contains;
				current_bag->contains[current_bag->contains_size] = _bag;
			}

			current_bag->contains_size++;
		} 

		free(color);
	}

	return current_bag;
}

void print_bags(struct bag *bag) {
	print_bag(bag);
	for(int i = 0; i < bag->contains_size; i++){
		print_bags(bag->contains[i]);
	}
}

void print_bag(struct bag *bag){
	if(bag == NULL){
		printf("[]\n");
		return;
	} 

	printf("{color: %s, qty: %d, contains_size: %d}\n",
			bag->color,
			bag->qty,
			bag->contains_size);
}

long unsigned int qty(struct bag *current_bag){
	long unsigned int sum = 0;
	for(int i = 0; i < current_bag->contains_size; i++){
		sum += qty(current_bag->contains[i]);
	}
	long unsigned int result = current_bag->qty + (current_bag->qty * sum);
	return result;
}

// struct bag{
//   int qty;
//   char *color;
//   struct bag **contains;
//   int contains_size;
// };
