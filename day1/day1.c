#include<stdio.h>
#include<stdlib.h>

int main(){
	FILE *file;
	file = fopen("day1.input", "r");

	int input[200];
	int j = 0;
	while (!feof (file))
	{
		int i= 0;
		fscanf (file, "%d", &i);
		input[j] = i;
		j++;

	}
	fclose (file);

	int result=0;

	for(int i = 0; i< 200; i++){
		for(int k = i+1; k< 200; k++){
			int first = input[i];
			int second = input[k];
			int sum = first + second;
			if(sum == 2020){
				result = first * second;	
				break;
			}

		} 

		if(result!=0){
			break;
		}

	}

	printf("result: %d\n",result);

	result = 0;
	for(int i = 0; i< 200; i++){
		for(int k = i+1; k< 200; k++){
			for(int l = k+1; l< 200; l++){
				int first = input[i];
				int second = input[k];
				int third = input[l];
				int sum = first + second + third;
				if(sum == 2020){
					result = first * second * third;	
					break;
				}
			}
		} 

		if(result!=0){
			break;
		}

	}
	printf("result: %d\n",result);
}


