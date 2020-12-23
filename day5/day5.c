#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define MAX_ROW 127

int main(){

  int all_seats[2000];
  int all_seats_index = 0;

  for(int a = 1; a < 127; a++){
    for(int b = 0; b < 8; b++){
      all_seats[all_seats_index] = (a * 8) + b;
      all_seats_index = all_seats_index +1;
    }
  }

  FILE *file;
  file = fopen("day5.input.full", "r");

  if(file == NULL){
    exit(EXIT_FAILURE);
  }

  char current[15];
  int highest_seat_id = 0;
  int lowest_seat_id = 1000;

  int existing_seats[2000];
  int existing_seats_index = 0;

  while(fgets(current, 15, file)){

    current[10]= '\0';

    int lower = 0;
    int upper = 127;

    for(int i=0; i < 6; i++){

      if(current[i] == 'F'){
	double _upper = (double) upper;
	double _lower = (double) lower;
	_upper = floor(_upper - (( _upper - _lower ) / 2.0));
	upper = (int) _upper;
      } else {
	double _upper = (double) upper;
	double _lower = (double) lower;
	_lower = ceil(_lower + (( _upper - _lower ) / 2.0));
	lower = (int) _lower;
      }

    }

    int row = 0;

    if(current[6] == 'F'){
      row = lower;
    } else {
      row = upper;
    }

    upper = 7;
    lower = 0;

    for(int i = 7; i < 9; i++){
      if(current[i] == 'L'){
	double _upper = (double) upper;
	double _lower = (double) lower;
	_upper = floor(_upper - (( _upper - _lower ) / 2.0));
	upper = (int) _upper;
      } else {
	double _upper = (double) upper;
	double _lower = (double) lower;
	_lower = ceil(_lower + (( _upper - _lower ) / 2.0));
	lower = (int) _lower;
      }

    }

    int range = 0;

    if(current[9] == 'L'){
      range = lower;
    } else {
      range = upper;
    }

    int seat_id = (row * 8) + range;

    if(seat_id > highest_seat_id) {
      highest_seat_id = seat_id;
    }

    if(seat_id < lowest_seat_id){
      lowest_seat_id = seat_id; 
    }

    existing_seats[existing_seats_index] = seat_id;
    existing_seats_index++;
  }

  printf("lowest_seat_id: %d, highest_seat_id: %d\n",lowest_seat_id, highest_seat_id);

  int missing_seats[2000];
  int missing_seats_index = 0;

  for(int k = 0; k < all_seats_index; k++){
    int a_seat = all_seats[k];
    int is_missing = -1;
    for(int l = 0; l < existing_seats_index; l++){
      int existing_seat = existing_seats[l];
      if(a_seat == existing_seat){
	is_missing = 0;
	break;
      }
    }

    if(is_missing == -1){
      missing_seats[missing_seats_index] = a_seat;
      missing_seats_index++;
    }

  }

  for(int i = 0; i < missing_seats_index; i++){
    printf("%d\n", missing_seats[i]);
  }

}
