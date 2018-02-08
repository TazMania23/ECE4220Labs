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

typedef struct sthreads{
	int Neo_matrix[][];
	int count[];
};


int main(argc, *argv[]) {

	if(argc!=3)
	{
		printf("\nWrong Amount of Arguments\n");
		return 0;
	}

	return EXIT_SUCCESS;
}
