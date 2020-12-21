#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define LINE_SIZE 31
#define FILE_SIZE 323


//    Right 1, down 1.
//    Right 3, down 1. 223 (This is the slope you already checked.)
//    Right 5, down 1.
//    Right 7, down 1.
//    Right 1, down 2.

long check_tree_in_slope(char  lines[FILE_SIZE][100], int right, int down);

int main(){
  FILE *file;
  file = fopen("day3.input","r");

  if (file == NULL){
    exit(EXIT_FAILURE);
  }


  char lines[FILE_SIZE][100];

  int currentLine = 0;
  while(fgets(lines[currentLine], 100, file)){
    lines[currentLine][LINE_SIZE] = '\0';
    currentLine++;
  }


  for(int i = 0; i< FILE_SIZE; i++){
    printf("%s\n", lines[i]);
  }

  long r1 = check_tree_in_slope(lines, 1, 1);
  long r2 = check_tree_in_slope(lines, 3, 1);
  long r3 = check_tree_in_slope(lines, 5, 1);
  long r4 = check_tree_in_slope(lines, 7, 1);
  long r5 = check_tree_in_slope(lines, 1, 2);

  printf("trees: %ld %ld %ld %ld %ld \n", r1, r2, r3, r4, r5);
  printf("results: %ld", r1*r2*r3*r4*r5);
  exit(EXIT_SUCCESS);
}

long check_tree_in_slope(char lines[FILE_SIZE][100], int right, int down){

  char tree = '#';

  int currentRow = 0;
  int trees = 0;
  int notrees = 0;
  int current_column = 0;
  char currentLine[LINE_SIZE];

  while(currentRow<FILE_SIZE){
    strcpy(currentLine, lines[currentRow]);

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

    if(currentRow < FILE_SIZE){
      current_column = current_column + right;
      if(current_column >= LINE_SIZE) current_column = current_column - LINE_SIZE;
    }

    currentRow = currentRow + down;
  }
  return trees;
}
