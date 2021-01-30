#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_CHAR 100


struct password{
	unsigned int lower;
	unsigned int higher; 
	char *letter;
	char *word;
};

void print_password(struct password *input);

void print_password(struct password *input){
	printf("{lower: %d, higher:%d, letter:%s, word:%s}\n", input->lower, input->higher, input->letter, input->word);
}

int main(){
  FILE *file;
  file = fopen("day2.input","r");

  char *current = malloc(100);
  size_t file_size = 0;
  char **lines=NULL;

  if (file == NULL){
    exit(EXIT_FAILURE);
  }

  int i = 0;

  while(fgets(current, MAX_CHAR, file)){
	  current[strlen(current) - 1] = '\0';
	  char **_lines = realloc(lines, (file_size + 1) * sizeof(char *));
	  if(_lines == NULL){
		  exit(EXIT_FAILURE);
	  }
	  lines = NULL;
	  lines = _lines;
	  lines[file_size] = current;
	  file_size++;

	  struct password *pass = malloc(sizeof(struct password));
	  pass->letter = malloc(2);
	  pass->word = malloc(100);

	  char minus;
	  char comma;
	  sscanf(lines[i],"%d %c %d %s %s", &(pass->lower), &minus, &(pass->higher), pass->letter, pass->word);

	  pass->letter[1] = '\0';

	  print_password(pass);
  }


  fclose(file);

  int success = 0;

//  for(int i = 0; i<1000; i++){
//    int a;
//    char minus;
//    int b;
//    char letter;
//    char comma;
//    char word[50];
//    sscanf(lines[i],"%d %c %d %c %c %s", &a, &minus, &b, &letter, &comma, word);
//
//    const int wordLength = strlen(word);
//
//    int count = 0;
//
//    for (int i = 0;i< wordLength; i++){
//      if(word[i] == letter) count++;
//    }
//
//    const int result = count >= a && count <= b;
//
//    if(result==1) success++;
//  }


  printf("succes: %d\n", success);

  exit(EXIT_SUCCESS);
}

