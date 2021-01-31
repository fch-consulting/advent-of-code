#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
  FILE *file;
  file = fopen("day6.input.full", "r");

  if(file==NULL){
    exit(EXIT_FAILURE);
  }

  char distinct[100];
  for(int i = 0; i < 100; i++){
    distinct[i] = '\0';
  }

  long unsigned int sum = 0;

  char current[100];

  long unsigned int previous_line_size = 0;

  while(fgets(current, 100, file)){
    current[strlen(current)-1] = '\0';

    printf("%s\n", current);
    
    if(strlen(current) == 0){
      printf(">> %s\n", distinct);
      sum = sum + strlen(distinct);

      for(int i = 0; i < 100; i++){
	distinct[i] = '\0';
      }
      previous_line_size = 0;
      continue;
    } else if (previous_line_size == 0){
     for(int i = 0; i < 100; i++){
       if(current[i] == '\0') {
	 break;
       }
       distinct[i] = current[i];
     } 
     previous_line_size = strlen(current);
    } else {

      char new_distinct[100];
      for(int i = 0; i <100; i++){
	new_distinct[i] = '\0';
      }

      for(int i = 0, k=0; i < 100; i++){

	char a = current[i]; 

	if(a == '\0'){
	  break;
	}

	for(int j = 0; j < 100; j++){

	  if(distinct[j] == '\0'){
	    break;
	  } else if(distinct[j] == a){
	    new_distinct[k] = a;
	    k++;
	    break;
	  }

	}

      }
      for(int i = 0; i< 100; i++){
	distinct[i] = new_distinct[i];
      }
    }
  }

  sum = sum + strlen(distinct);

  printf("result: %ld\n", sum);

}
