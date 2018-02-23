/*
 ============================================================================
 Name        : Lab2Week2.c
 Author      : Tsiania Hughes
 Version     :
 Copyright   : Your copyright notice: it's mine, Taz
 Description : Hello World in C, Ansi-style
 ============================================================================
 */



#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sched.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/timerfd.h>
#include <time.h>
#include <pthread.h>
#include <string.h>

#define MY_PRIORITY 51  // kernel is priority 50
char holdline[100];
//I got demo to work
typedef struct{
	int id;
	int start_s;
	int start_n;
	int period_s;
	int period_n;
	char fname[15];

}Basic;
//had to make second struct bc the sum thread will have multiple lines of lyrics
//not just one
typedef struct{
	int id;
	int start_s;
	int start_n;
	int period_s;
	int period_n;
	char lyrics[20][100];
//20 lines with who knows how many charactes, not checking
}Just_Once;

//where the single sum thread
void Sumthread(void *ptr){
	printf("Hi there\n");
	int timer=timerfd_create(CLOCK_MONOTONIC, 0);

	struct itimerspec itval;
	struct sched_param param;

	param.sched_priority = MY_PRIORITY;
	sched_setscheduler(0, SCHED_FIFO, &param);
	//holding the struct pointer
	Just_Once *hold= (Just_Once*)ptr;

	itval.it_interval.tv_sec= hold->period_s;
	itval.it_interval.tv_sec= hold->period_n;

	itval.it_interval.tv_sec= hold->start_s;
	itval.it_interval.tv_sec= hold->start_n;
	printf("Hithere2\n");
	timerfd_settime(timer, 0, &itval, NULL);

	uint64_t numPeriods=0;
	//1 period pause
	read(timer, &numPeriods, sizeof(numPeriods));
	int x=0;
	while(x<20)
	{
		strcpy(hold->lyrics[x],holdline);
		read(timer, &numPeriods, sizeof(numPeriods));
		x++;
	
		printf("Hithere2");
		if(numPeriods>1)
		{
			printf("\n-----Missed-----");
			exit(1);
		}
	}
	pthread

}
//Where the two threads will be created
void MultiThreads(void *ptr){
	printf("Hello there\n");
	// timer setup
	int timer=timerfd_create(CLOCK_MONOTONIC, 0);

	struct itimerspec itval;
	struct sched_param param;

	param.sched_priority = MY_PRIORITY;
	sched_setscheduler(0, SCHED_FIFO, &param);
	//holding the struct pointer
	Basic *hold= (Basic*)ptr;

	itval.it_interval.tv_sec= hold->period_s;
	itval.it_interval.tv_sec= hold->period_n;

	itval.it_interval.tv_sec= hold->start_s;
	itval.it_interval.tv_sec= hold->start_n;

	//opening file
	FILE *fptr;
	fptr=fopen(hold->fname,"r");
	if(fptr==NULL)
	{
		printf("\nFailed to Open File %s", hold->fname);
		exit(1); //exit fail =1
	}
printf("Hello There 2\n");
	timerfd_settime(timer, 0, &itval, NULL);

	uint64_t numPeriods=0;
	//1 period pause
	read(timer, &numPeriods, sizeof(numPeriods));

	while(!feof(fptr))
	{
		//finish fscanf
		//fscanf(fptr, "%s", holdline);
		fgets(holdline, 100,fptr);
		read(timer, &numPeriods, sizeof(numPeriods));
	}
	fclose(fptr);
printf("HelloThere3\n");
	if(numPeriods>1)
	{
		printf("\n-----Missed-----");
		exit(1);
	}

}


int main(void)
{
	//looping variable
	int x=0;
	//getting all the information needed to run
	Basic vfirst ={1, 0,1000000, 0, 4000000, "first.txt"};
	Basic vsecond={2, 0,3000000, 0, 4000000, "second.txt"};
	Just_Once vthird ={3,0 ,2000000, 0, 2000000};

	printf("\nIt's Running!!!\n");

	pthread_t thread1,thread2,thread3;
	//thread 1 & 2 go to the multithreads and thread 3 goes to sum
	pthread_create(&thread1, NULL,(void *)&MultiThreads, (void *)&vfirst);
	pthread_create(&thread2, NULL,(void *)&MultiThreads, (void *)&vsecond);
	pthread_create(&thread3, NULL,(void *)&Sumthread, (void *)&vthird);

	printf("Half way there\n");

	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	pthread_join(thread3,NULL);
//print out the song
	for(x=0;x<20;x++)
	{
		printf("Line %d: %s\n", x,vthird.lyrics[x]);
		x++;
	}

	printf("Done\n");
	return 0;
}
