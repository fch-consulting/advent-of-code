#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int correct_password(char * password);
int is_good_ecl(char * password);
int is_correct_passport_id(char *input);
int is_valid_expiration_year(char *input);
int is_correct_hair_color(char *input);
int is_valid_birth_year(char *input);
int is_valid_issue_year(char *input);
int is_valid_height(char *input);

int main(){

  FILE *file;
  file = fopen("day4.input.full","r");

  if (file == NULL){
    exit(EXIT_FAILURE);
  }

  int currentLine = 0;

  char previous[2000];
  char current[2000];
  memset(previous, '\0', 2000); 

  int isNew = 0;
  int result = 0;

  while(fgets(current, 2000, file)){

    current[strlen(current)-1] = '\0';

    if(isNew>0){
      strcat(previous, " ");
    }

    strcat(previous, current);

    if(strlen(current) == 0){

      // remove the last space.
      previous[strlen(previous) - 1] = '\0';

      int is_correct = correct_password(previous);

      if(is_correct == 0){
	result++;
      }

      memset(previous, '\0', 2000); 
      isNew = 0;
      currentLine++;
      continue;
    }
    
    isNew ++;
    currentLine++;
  }

  int is_correct = correct_password(previous);

  if(is_correct == 0) result++;

  printf("result: %i\n", result ++);

}

int correct_password(char * password){


  char input[strlen(password)];
  strcpy(input, password);
  input[strlen(password)] = '\0';

  int nb_spaces = 0;

  for(long unsigned int k=0; k<sizeof(input); k++){
    if(input[k] == ' ') nb_spaces ++;
  }

  int nb_words = nb_spaces + 1;
  
  char *pass[nb_words];
  char *pass1 = strtok(input, " ");
  int i = 0;

  while(pass1){
    pass[i] = malloc(strlen(pass1)+1);
    strcpy(pass[i], pass1);
    pass[i][strlen(pass1)] = '\0';
    i++;
    pass1 = strtok(NULL, " ");
  }

  char * passport_headers[nb_words];
  char * passport_values[nb_words];

  for(int j = 0; j<nb_words; j++){
    char *a = pass[j];
    char *b = strtok(a, ":");
    char *c = strtok(NULL, ":");
    passport_headers[j] = malloc(4);
    passport_values[j] = malloc(10);
    strcpy(passport_headers[j], b);
    strcpy(passport_values[j], c);
    passport_headers[j][3] = '\0';
  }

  int existing_headers = sizeof(passport_headers) / ( sizeof(passport_headers[0]) );

  const char * should_be_headers[] = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"}; 
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
  
  if(result == 0){
    for(int i = 0; i < nb_words; i++){
      char *header = passport_headers[i];
      if(strcmp(header, "ecl")==0){
	int good_ecl = is_good_ecl(passport_values[i]);
	result = result + good_ecl;
      } else if(strcmp(header, "pid")==0){
	//printf("%s\n", header);
	int correct_passport_id = is_correct_passport_id(passport_values[i]);
	result = result + correct_passport_id;
      } else if(strcmp(header, "eyr")==0){
	int valid_expiration_year = is_valid_expiration_year(passport_values[i]);
	result = result + valid_expiration_year;
      } else if(strcmp(header, "hcl")==0){
	int correct_hair_color = is_correct_hair_color(passport_values[i]);
	result = result + correct_hair_color;
      } else if(strcmp(header, "byr")==0){
	int valid_birth_year = is_valid_birth_year(passport_values[i]);
	result = result + valid_birth_year;
      } else if(strcmp(header, "iyr")==0){
	int valid_issue_year = is_valid_issue_year(passport_values[i]);
	result = result + valid_issue_year;
      } else if(strcmp(header, "hgt")==0){
	int valid_height = is_valid_height(passport_values[i]);
	result = result + valid_height;
      }
    }
  }

  return result;
}

int is_valid_height(char *input){
  int result = 1;
  if(strstr(input, "cm") != NULL){
    unsigned long height = strtoul(input, NULL, 10);
    if(height >= 150 && height <= 194){
      result = 0;
    }
  } else if (strstr(input, "in") != NULL){
    unsigned long height = strtoul(input, NULL, 10);
    if(height >= 59 && height <= 76){
      result = 0;
    }
  }

  return result;
}

int is_valid_issue_year(char *input){
  int result = 1;
  
  unsigned long value = strtoul(input, NULL, 10);

  if(value <=2020 && value >= 2010){
    result = 0;
  }

  return result;
}

int is_valid_birth_year(char *input){
  int result = 1;
  
  unsigned long value = strtoul(input, NULL, 10);

  if(value <=2002 && value >= 1920){
    result = 0;
  }

  return result;
}

int is_correct_hair_color(char *input){
  int result = 1;

  const char *accepted_values = "abcdef0123456789";

  int input_lenght = strlen(input);

  if(input_lenght == 7){

    for(int i = 0; i < input_lenght; i++){

      if(i == 0){
	if(input[0] == '#'){
	  continue;
	} else {
	  return 1;
	}
      } else {
	char current_input = input[i];
	for(long unsigned int j = 0; j < strlen(accepted_values); j++){
	  if(current_input == accepted_values[j]){
	    break;
	  }

	  if(j == strlen(accepted_values) - 1){
	    return 1;
	  }

	}
      }
    }
    result = 0;
  }

  return result;
}

int is_valid_expiration_year(char *input){
  int result = 1;
  
  unsigned long value = strtoul(input, NULL, 10);

  if(value <=2030 && value >= 2020){
    result = 0;
  }

  return result;
}

int is_good_ecl(char *input){
  int result = 1;
  const char *ecls[] = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
  int ecls_lenght = sizeof(ecls) / sizeof(ecls[0]);
  for(int i = 0; i < ecls_lenght; i++){
    if(strcmp(ecls[i], input) == 0) {
      result = 0;
      break;
    }
  }

  return result;
}

int is_correct_passport_id(char *input){
  int result = 1;

  if(strlen(input)==9){
    result = 0;
  }

  return result;
}
