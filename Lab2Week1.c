/*
============================================================================
Name        : Lab2Week1.c
Author      : Tsiania Hughes
Version     :
Copyright   : Your copyright notice: it's mine, Taz
Description : Hello World in C, Ansi-style
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
//struct
typedef struct {
	
	int neo_matrix[20][100];	//max txt file length & width
	int count[100];		
	int r;
	int c;
	int clue;
}sthreads;

void *OneThreadToRuleThemAll(void *ptr) {
	//getting info from ptr 
	sthreads *info = (sthreads*) ptr;
	int num = (*info).clue;
	int rows = (*info).r;
	int cols = (*info).c;
	//variables
	int x, y;
	//start
	printf("\nUsing one thread to find %d", num); //info vs (*info)

	
	pthread_exit(0);
}
void *OneThreadR(void *ptr) {

	pthread_exit(0);
}
void *OneThreadC(void *ptr) {
	
	pthread_exit(0);
}

void *OneThreadE(void *ptr) {

	pthread_exit(0);
}

int main(int argc, char *argv[]) {
	//variables
	int targetNum;
	int rows;
	int cols;

	sthreads hold;

	// a.out,  text file and target number
	if (argc != 3)
	{
		printf("\nWrong Amount of Arguments\n");
		return 0;
	}
	//collecting variables from file
	FILE *fptr = fopen(argv[1], "r");
	if (fptr == NULL)
	{
		printf("\nFile not Found or Incorrect placing");
		printf("\n ./Lab2Part1 matrix.txt #");
		return 0;
	}
	//getting row and col
	fscanf(fptr, "%d %d", rows, cols);

	hold.r = rows;
	hold.c = cols;
	printf("\nRows and Coloums found");
	//getting target num
	if (isdigit(atoi(argv[2])) != 0) //small check
		targetNum = atoi(argv[2]);
	//storing it into hold 
	hold.clue = targetNum;
	//getting values out of text file into hold
	while (!(feof(fptr))) {
		for (int x = 0; x<rows; x++)
			for (int y = 0; y<cols; y++)
			{
				fscanf(fptr, "%d ", &hold.neo_matrix[x][y]);
			}

	}
	fclose(fptr);

	//Setting up the Timers now
	struct timespec startingT, endingT;
	
	
	//1 thread for whole matrix
	pthread_t T1;
	pthread_create(&T1, NULL, (void*)&OneThreadToRuleThemAll, (void*)&hold);
	pthread_join(T1, NULL);

	//1 thread for searching each row
	pthread_t T2;
	pthread_create(&T2, NULL, (void*)&OneThreadR, (void*)&hold);
	pthread_join(T2, NULL);
	//1 thread for searching each column
	pthread_t T3;
	pthread_create(&T3, NULL, (void*)&OneThreadC, (void*)&hold);
	pthread_join(T3, NULL);
	//1 thread for each element

	pthread_t T4;
	pthread_create(&T4, NULL, (void*)&OneThreadE, (void*)&hold);
	pthread_join(T4, NULL);
	return 0;
}
