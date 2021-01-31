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
  while(fgets(current, 100, file)){
    current[strlen(current)-1] = '\0';
    
    if(strlen(current) == 0){
      sum = sum + strlen(distinct);

      for(int i = 0; i < 100; i++){
	distinct[i] = '\0';
      }
      continue;
    }

    for(int i = 0; i < 100; i++){
      char a = current[i]; 
      if(a == '\0'){
	break;
      }

      for(int j = 0; j < 100; j++){

	if(distinct[j] == '\0'){
	  distinct[j] = a;
	  break;
	} else if(distinct[j] == a){
	  break;
	}

      }

    }

  }

  sum = sum + strlen(current);

  printf("result: %ld", sum);

}
