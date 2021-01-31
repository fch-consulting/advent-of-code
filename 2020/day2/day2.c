#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_CHAR 100

int main(){
  FILE *file;
  file = fopen("day2.input","r");

  char line[MAX_CHAR];
  char lines [1000][MAX_CHAR + 1]; 

  if (file == NULL){
    exit(EXIT_FAILURE);
  }

  int i = 0;

  while(fgets(line, MAX_CHAR, file)){
    strncpy(lines[i],line, MAX_CHAR);
    i++;
  }

  fclose(file);

  int success = 0;

  for(int i = 0; i<1000; i++){
    int a;
    char minus;
    int b;
    char letter;
    char comma;
    char word[50];
    sscanf(lines[i],"%d %c %d %c %c %s", &a, &minus, &b, &letter, &comma, word);

    const int wordLength = strlen(word);

    int count = 0;

    for (int i = 0;i< wordLength; i++){
      if(word[i] == letter) count++;
    }

    const int result = count >= a && count <= b;

    if(result==1) success++;
  }


  printf("succes: %d\n", success);

  exit(EXIT_SUCCESS);
}

