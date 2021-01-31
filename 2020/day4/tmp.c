#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(){

  char input[] = "ecl:gry pid:860033327 eyr:2020 hcl:#fffffd byr:1937 iyr:2017 cid:147 hgt:183cm";

  int nb_spaces = 0;
  for(int k=0;k<sizeof(input);k++){
    if(input[k] == ' ') nb_spaces ++;
  }

  int nb_words = nb_spaces + 1;
  
  char *pass[nb_words];
  char *pass1  = strtok(input, " ");
  int i = 0;

  while(pass1){
    pass[i] = malloc(sizeof(pass1));
    strcpy(pass[i], pass1);
    pass1 = strtok(NULL, " ");
    i++;
  }

  char * passport_headers[nb_words];

  for(int j = 0;j<nb_words;j++){
    char *a = pass[j];
    char *b = strtok(a, ":");
    char *c = strtok(NULL, ":");
    printf("%s\n", b);
    printf("%s\n", c);
    passport_headers[j] = malloc(3);
    strcpy(passport_headers[j], b);
  }

  int existing_headers = sizeof(passport_headers) / ( sizeof(passport_headers[0]) );

  char * should_be_headers[] = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "cid"}; 
  int total_headers = sizeof(should_be_headers) / ( sizeof(should_be_headers[0]) );

  int success = 0;
  for(int j=0; j<total_headers; j++){
    for(int k=0; k < existing_headers; k++){
      int cmp = strcmp(passport_headers[k], should_be_headers[j]);
      if(cmp == 0){
	success ++;
      }
    }
  }

  int result = success - total_headers;
  printf("%d\n", result);

}
