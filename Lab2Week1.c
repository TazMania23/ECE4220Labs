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
//struct
typedef struct{
	int neo_matrix[][];
	int count[];
}sthreads;

void *OneThreadToRuleThemAll(int ptr[][]){


}
void *OneThreadR(void *ptr){

}
void *OneThreadC(void *ptr){

}

void *OneThreadE(void *ptr){

}

int main(argc, *argv[]) {
	//variables
	int targetNum;
	int rows;
	int cols;

	sthreads hold=hold.neo_matrix[rows][cols];

	// a.out,  text file and target number
	if(argc!=3)
	{
		printf("\nWrong Amount of Arguments\n");
		return 0;
	}
	//collecting variables from file
	FILE *fptr=fopen(argv[1],"r");
	if(fptr==NULL)
		{
			printf("\nFile not Found or Incorrect placing");
			printf("\n Lab2.out matrix.txt #");
			return 0;
		}
	fscanf(fptr, "%d %d", rows, cols);



	sthreads hold=hold.neo_matrix[rows][cols];
	//getting target num
	if(isdigit(atoi(argv[2]))!=0) //small check
		targetNum=atoi(argv[2]);
	//getting values out of text file into hold
	while(!(feof(fptr))){
		for(int x=0;x<rows; x++)
			for(int y=0;y<cols;y++)
			{
				fscanf(fptr,"%d ",hold.neo_matrix[x][y]);
			}

	}
	fclose(fptr);



	return 0;
}
