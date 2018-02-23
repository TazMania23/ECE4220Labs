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
	int count[250];		
	int r;
	int c;
	int clue;
;
}sthreads;

//made another struct, wasn't sure how to differeniate which thread was which
typedef struct {
	//thread id
	int tid[100];
	sthreads *storage;
}otherThreads;

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
	for(x=0;x<rows;x++)
		for(y=0;y<cols;y++)
		{
			if ((*sthreads).neo_matrix[x][y]==num;
			    ++(*sthreads).count[0];
		}
	printf("\n-------- The number %d was found %d times in the matrix --------",clue ,(*sthreads).count[0]);
	//dont forget to end thread
	pthread_exit(0);
}
void *OneThreadR(void *ptr) {

	//getting info from ptr 
	otherThreads *Tinfo = (otherThreads*) ptr;
	sthreads *Ginfo= Tinfo->storage;
	
	int id= Tinfo->tid;
	int num = (*Ginfo).clue;
	int rows = (*Ginfo).r;
	
	int x;
	for(x=0;x<rows;x++)
	{
		if((*Ginfo).neo_matrix[id][x]==num)
			++(*Ginfo).count[id];
	}
	
	pthread_exit(0);
}
void *OneThreadC(void *ptr) {
	
	//getting info from ptr 
	otherThreads *Tinfo = (otherThreads*) ptr;
	sthreads *Ginfo= Tinfo->storage;
	
	int id= Tinfo->tid;
	int num = (*Ginfo).clue;
	int cols = (*Ginfo).c;
	
	int x;
	for(x=0;x<cols;x++)
	{
		if((*Ginfo).neo_matrix[x][id]==num)
			++(*Ginfo).count[id];
	}
	
	pthread_exit(0);
}

void *OneThreadE(void *ptr) {

	//getting info from ptr 
	otherThreads *Tinfo = (otherThreads*) ptr;
	sthreads *Ginfo= Tinfo->storage;
	
	int id= Tinfo->tid;
	int num = (*Ginfo).clue;
	int rows = (*Ginfo).r;
	int cols = (*Ginfo).c;
	int x;
	//no for loop needed since there will be a thread for each element
		if((*Ginfo).neo_matrix[rows][cols]==num)
			++(*Ginfo).count[id];
	
	
	pthread_exit(0);
}

int main(int argc, char *argv[]) {
	//variables
	int targetNum;
	int rows;
	int cols;
	int x,y;
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
	hold.tid={0};
	printf("\nRows and Coloums found");
	//getting target num
	if (isdigit(atoi(argv[2])) != 0) //small check
		targetNum = atoi(argv[2]);
	//storing it into hold 
	hold.clue = targetNum;
	//getting values out of text file into hold
	while (!(feof(fptr))) {
		for (x = 0; x<rows; x++)
			for (y = 0; y<cols; y++)
			{
				fscanf(fptr, "%d ", &hold.neo_matrix[x][y]);
			}

	}
	fclose(fptr);

	//Setting up the Timers now
	struct timespec startingT, endingT;
	unsigned int number;
	
	clock_gettime(CLOCK_MONOTONIC, &startingT);
	
	//1 thread for whole matrix
	pthread_t T1;
	pthread_create(&T1, NULL, (void*)&OneThreadToRuleThemAll, (void*)&hold);
	pthread_join(T1, NULL);

	clock_gettime(CLOCK_MONOTONIC, &endingT);
	
	number=1000000000 *(endingT.tv_sec - startingT.tv_sec)+ endingT.tv_nsec - startingT.tv_nsec;
	printf("\nOne Thread to search whole matrix took %u ns\n\n", number);
	
	//since hold is getting passed into everything count must reset after ever thread finishes
	int reset=0;
	for(reset=0;reset<250;reset++)
		hold.count[reset]=0;
	
	//1 thread for searching each row
	
	pthread_t T2[rows];
	otherThreads T2_info[rows]
	clock_gettime(CLOCK_MONOTONIC, &startingT);
	for(x=0;x<rows;x++)
	{
		//had issues here implementing
		T2_info[x].tid=x;
		T2_info[x].storage= &hold;
		pthread_create(&T2[x], NULL, (void*)&OneThreadR, (void*)&T2_info[x]);
	}
	for(x=0;x<rows;x++)
		pthread_join(T2[x], NULL);

	clock_gettime(CLOCK_MONOTONIC, &endingT);
	number=1000000000 *(endingT.tv_sec - startingT.tv_sec)+ endingT.tv_nsec - startingT.tv_nsec;
	printf("\nOne Thread per each row in matrix took %u ns", number);
	
	//Sicne theres multiple threads per row to find the total loop all threads and add up
	//their count values
	int countByrow=0;
	for(x=0;x<250;x++)
		countByrow+=hold.count[x];
	
	printf("\nSearching: %d \tCounts: %d\n\n",targetNum, countByrow); 
	//counter reset
	for(reset=0;reset<250;reset++)
		hold.count[reset]=0;
	
	//1 thread for searching each column
	//basically copy and paste from the other one just change row to col
	//please work right
	pthread_t T3[cols];
	otherThreads T3_info[cols];
	
	clock_gettime(CLOCK_MONOTONIC, &startingT);
	
	for(x=0;x<cols;x++)
	{
		//had issues here implementing
		T3_info[x].tid=x;
		T3_info[x].storage= &hold;
		pthread_create(&T3[x], NULL, (void*)&OneThreadC, (void*)&T3_info[x]);
	}
	for(x=0;x<cols;x++)
		pthread_join(T3[x], NULL);

	clock_gettime(CLOCK_MONOTONIC, &endingT);
	number=1000000000 *(endingT.tv_sec - startingT.tv_sec)+ endingT.tv_nsec - startingT.tv_nsec;
	printf("\nOne Thread per each column in matrix took %u ns", number);
	
	//Sicne theres multiple threads per row to find the total loop all threads and add up
	//their count values
	int countBycol=0;
	for(x=0;x<250;x++)
		countBycol+=hold.count[x];
	
	printf("\nSearching: %d \tCounts: %d\n\n",targetNum, countBycol); 
	//counter reset
	for(reset=0;reset<250;reset++)
		hold.count[reset]=0;
	
	//1 thread for each element
	int totalElements=rows*cols;
	
	pthread_t T4[totalElements];
	otherThreads T4_info[totalElements];
	clock_gettime(CLOCK_MONOTONIC, &startingT);
	
	
	for(x=0;x<totalElements;x++)
	{
		//had issues here implementing
		T4_info[x].tid=x;
		T4_info[x].storage= &hold;
		pthread_create(&T4[x], NULL, (void*)&OneThreadE, (void*)&T4_info[x]);
	}
	
	for(x=0;x<totalElements;x++)
		pthread_join(T4[x], NULL);

	clock_gettime(CLOCK_MONOTONIC, &endingT);
	number=1000000000 *(endingT.tv_sec - startingT.tv_sec)+ endingT.tv_nsec - startingT.tv_nsec;
	printf("\nOne Thread per each row in matrix took %u ns", number);
	
	//Sicne theres multiple threads per row to find the total loop all threads and add up
	//their count values
	int countByE=0;
	for(x=0;x<250;x++)
		countByE+=hold.count[x];
	
	printf("\nSearching: %d \tCounts: %d\n\n",targetNum, countByE); 
	//counter reset
	for(reset=0;reset<250;reset++)
		hold.count[reset]=0;
	
	
	//Done hopefully -_-
	
	
	return 0;
}
