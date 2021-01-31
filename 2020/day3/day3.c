#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define LINE_SIZE 31
#define FILE_SIZE 323

int main(){
  FILE *file;
  file = fopen("day3.input","r");
  char currentLine[100];
  //char currentLine[LINE_SIZE+1];

  if (file == NULL){
    exit(EXIT_FAILURE);
  }

  char tree = '#';

  int currentRow = 0;
  int trees = 0;
  int notrees = 0;

  int current_column=0;

  while(fgets(currentLine, 100, file)){
    currentLine[LINE_SIZE] = '\0';
    if(currentRow != 0){
      if(currentLine[current_column] == tree){
	trees ++;
      } else {
	notrees ++;
      }
      currentLine[current_column] = 'O';
    }

    currentLine[current_column] = 'O';
    printf("%s\n", currentLine);

    if(currentRow != FILE_SIZE){
      current_column = current_column + 3;
      if(current_column >= LINE_SIZE) current_column = current_column - LINE_SIZE;
    }
    
    currentRow++;
  }

  printf("%d  %d\n", trees, notrees);
  exit(EXIT_SUCCESS);
}
