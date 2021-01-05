#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct bag *create_structure(char *line); 

// this structure represents the current bags, with the name of the bag it contains.
struct bag {
  char *bag_name;
  int numberOfBagsType;
  char **contains_bag;
};

int main(){

  FILE *file;
  file = fopen("day7.input.full", "r");

  if(file == NULL){
    exit(EXIT_FAILURE);
  }

  char *current = malloc(1000);

  char **bag_str=NULL; // array of string from files

  int number_of_entries = 0;

  while(fgets(current, 1000, file)){
    current[strlen(current)-1]='\0'; // remove the \n

    if(strstr(current, "other")!=NULL){
      continue;
    }

    // copy the inputs to an array
    if(bag_str == NULL){
      bag_str = malloc(sizeof(char *));
      *(bag_str) = malloc(strlen(current)+1);
      strcpy(*(bag_str), current);
    } else {
      char **_bag_str= realloc(bag_str, (number_of_entries + 1) * sizeof(char *));
      if(_bag_str == NULL){
	exit(EXIT_FAILURE);
      }
      bag_str = NULL;
      bag_str = _bag_str;
      *(bag_str+number_of_entries) = malloc(strlen(current)+1);
      strcpy(*(bag_str+number_of_entries), current);
    }

    number_of_entries++;
  }
  free(current); //clean the last current entry
  fclose(file);  // close the file;
  // end copy the input str to an array

  // create the array of struct bags
  struct bag *bags[number_of_entries];
  for(int i = 0; i<number_of_entries; i++){
    struct bag *b = create_structure(*(bag_str+i));
    bags[i] = b;
  }
  // end create the array of struct bags

  // we can start working
  // lets check for all the bags that contains 'shiny gold bags'.
  char **results_bags = malloc(sizeof(char *));
  results_bags[0] = malloc(strlen("shiny gold bags") +1);
  strcpy(results_bags[0], "shiny gold bags");
  unsigned int results_bags_index = 1;

  for(int a = 0; a< results_bags_index; a++){

    for(int i = 0; i<number_of_entries; i++){
      for(int j = 0; j<bags[i]->numberOfBagsType; j++){
	if(strncmp(bags[i]->contains_bag[j], results_bags[a], strlen(results_bags[a])-2)==0){


	  // check if the bag is already in result;
	  unsigned int bag_in_result = 0;
	  for(int b = 0; b<results_bags_index; b++){
	    if(strncmp(bags[i]->bag_name, results_bags[b], strlen(results_bags[b])-2) == 0){
	      bag_in_result ++;
	      break;
	    }
	  }

	  if(bag_in_result > 0){
	    continue;
	  }


	  char **_results_bags= realloc(results_bags, (results_bags_index + 1) * sizeof(char *));
	  if(_results_bags==NULL){
	    exit(EXIT_FAILURE);
	  }

	  results_bags = NULL;
	  results_bags = _results_bags;
	  results_bags[results_bags_index] = malloc(strlen(bags[i]->bag_name)+1);
	  strcpy(results_bags[results_bags_index], bags[i]->bag_name);
	  results_bags_index ++;
	  break;
	}

      }
    }

  }


  for(int i=0; i<results_bags_index; i++){
    free(results_bags[i]);
  }

  free(results_bags);

  results_bags_index = results_bags_index - 1;
  printf("results: %d\n", results_bags_index);

  // free  bag_str
  for(int i = 0; i<number_of_entries; i++){
    free(bags[i]->bag_name);
    for(int k = 0; k < bags[i]->numberOfBagsType; k++){
      free(bags[i]->contains_bag[k]);
    }

    free(bags[i]->contains_bag);
    free(bags[i]);
    free(*(bag_str+i));
  }

  free(bag_str);
  // end free bag_str

}

struct bag *create_structure(char *line) {
  char *tail = strstr(line, "contain");
  unsigned int index = (unsigned int) (tail-line);

  struct bag *b;
  b = (struct bag*) malloc(sizeof(struct bag));
  b->bag_name = malloc(index);
  strncpy(b->bag_name, line, index);
  b->bag_name[index-1] = '\0';

  tail = tail + 10;

  int i = 1;

  char *t = strstr(tail, ",");

  while(t){
    index = t - tail;
    char *k = malloc(index+1);
    strncpy(k, tail, index);
    k[index] = '\0';

    tail = tail + index + 4;

    if(i>1){
      char **_tails = realloc(b->contains_bag, (size_t) (i * sizeof(char *)));
      if(_tails == NULL){
	exit(EXIT_FAILURE);
      }
      b->contains_bag = NULL;
      b->contains_bag = _tails;
      b->contains_bag[i-1] = k;
    } else {
      b->contains_bag = malloc(sizeof(char *));
      b->contains_bag[0] = k;
    } 

    i++;
    t = strstr(tail, ",");
  }

  char *final = malloc(strlen(tail)+1);
  memset(final, '\0', strlen(tail)+1);
  strncpy(final, tail, strlen(tail)-1);

  b->numberOfBagsType = i;

  if(i>1){
    char **_tails = realloc(b->contains_bag, (size_t) (i * sizeof(char *)));
    if(_tails == NULL){
      exit(EXIT_FAILURE);
    }
    b->contains_bag = NULL;
    b->contains_bag = _tails;
    b->contains_bag[i-1] = final;
  } else {
    b->contains_bag = malloc(sizeof(char *));
    b->contains_bag[0] = final;
  }

  return b;
}
