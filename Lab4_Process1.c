/*
 ============================================================================
 Name        : Lab4_Main.c
 Author      : Tsiania Hughes
 Version     :
 Copyright   : Your copyright notice: it's mine, Taz
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>		// standard symbolic constants and types (e.g. NULL); usleep
#include <wiringPi.h>	// needed for the wiringPi functions
#include <pthread.h>
#include <sched.h>
#include <sys/types.h>
#include <fcntl.h>
#include <time.h>
#include <stdbool.h>
#include <sched.h>
#include <pthread.h>

#include "ece4220lab3.h"
//said it couldnt find it?
void Kidthreads(void *ptr);
void print(void *ptr);



#define SCHED_POLICY SCHED_FIFO
//for gps numbers
typedef struct{
	//location
	int loc;
	//locations with corrosponding time stamp
	unsigned int time_stampS;
	unsigned int time_stampN;
	//pipe for extra credit
	int numPipe;
}gps;

//for process2 data
typedef struct{
	//previous location
	int prevLoc;
	//previous times broken into secs and nsecs
	unsigned int prevTs;
	unsigned int prevTn;
	//after location
	int afterLoc;
	//after times into secs and nsecs
	unsigned int afterTs;
	unsigned int afterTn;
	//current times secs and nsecs
	unsigned int nowTs;
	unsigned int nowTn;
	//pipe number for extra credt
	int numPipe;
}gps_m;

//bonus credit struct
typedef struct{
	float finLoc;
	unsigned int finTime;
}printer;


//add printing struct for extra credit

//Global Variable to share program starting time
struct timespec startingT;

void Parthread(void *ptr)
{
	//this is recieving buffer
	gps *info= (gps *) ptr;
	//child thread
	pthread_t childT, pthread1;

	//timers for start and timeP2 is recieved. Will get rid of
	//struct timespec startT, timeP2;

	//pipe2 id
	int pipe_two;

	//pipe2 is sending a Boolean
	bool PB=0;

	//pipe2 open
	if((pipe_two =open("N_pipe2", O_RDONLY))<0)
		{
			printf("\nN_pipe2 couldn't be opened Main\n");
		}

	printf("\nPipe2 opened");
	int SimPipe[2];
	if(pipe(SimPipe)<0)
		printf("\nCreating Pipe in Function: Parthread failed");

	info->numPipe=SimPipe[1];
	printf("\nCreating Pthread1 next\n");
	pthread_create(&pthread1, NULL, (void *)print, (void *) &SimPipe[0]);





	//getting starting time for this thread
	//clock_gettime(CLOCK_MONOTONIC, &startT);
	while(1)
	{
		if(read(pipe_two,&PB, sizeof(PB))<0)
		{
			printf("\nN_pipe2 read error Main\n");
		}
			//getting the time stamp Pipe2
			//clock_gettime(CLOCK_MONOTONIC, &timeP2);

			//printing PushButton times just as a check before
			//printf("\nPushbutton Time-Stamp from Pipe2 being opened to read: Seconds: %u NanoSeconds: %u", (timeP2.tv_sec-startT.tv_sec),(timeP2.tv_nsec-startT.tv_nsec));

			//creating child thread
			pthread_create(&childT, NULL, (void*)Kidthreads,(void *)info);

	}
}

void Kidthreads(void *ptr)
{
	//variables
	gps *info= (gps *) ptr;
	struct timespec timeK;

	//hold time math stuff
	double currentT, beforeT, afterT, beforeLoc, afterLoc;
	float crossRef;

	//passing data to location data struct variable
	gps_m Data;
	Data.prevLoc= info->loc;
	Data.prevTs= info->time_stampS;
	Data.prevTn= info->time_stampN;

	//getting now time, NOT SURE IF ITS SUPPOSE TO BE REAL, MIGHT NOT MATTER
	clock_gettime(CLOCK_MONOTONIC, &timeK);
	Data.nowTs= timeK.tv_sec- startingT.tv_sec;
	Data.nowTn= timeK.tv_nsec- startingT.tv_nsec;

	//code was freaking out so I added a delay
	while(Data.prevTs==info->time_stampS && Data.prevTn==info->time_stampN)
	{
		usleep(20);
	}


	Data.afterLoc= info->loc;
	Data.afterTs=info->time_stampS;
	Data.afterTn=info->time_stampN;

	currentT= ((double)Data.nowTs) +   ((double)Data.nowTn/1000000000);
	beforeT= ((double)Data.prevTs) +  ((double)Data.prevTn/1000000000);
	afterT= ((double)Data.afterTs) + ((double)Data.afterTn/1000000000);
	beforeLoc= Data.prevLoc;
	afterLoc= Data.afterLoc;

	crossRef= (float)(beforeLoc +((float)currentT-(float)beforeT)*(afterLoc-beforeLoc)/((float)afterT-(float)beforeT));
	
	printf("\n\nKidThread Printf -> Location is %f at Time: %lf\n", crossRef, currentT);

	//printing
	printer p1;
	p1.finLoc=crossRef;
	p1.finTime=currentT;

	write(info->numPipe, &p1, sizeof(printer));

	pthread_exit(0);
}

void print(void *ptr)
{
	int *pipeHold= (int*)ptr;
	int simPipe= *pipeHold;
	printer printInfo;

	while(1)
	{
		read(simPipe, &printInfo, sizeof(printer));
	//	printf("Location: %f  \t Seconds: %u  NanoSeconds: %u", printInfo.finLoc,printInfo.finTime);
	}
}



int main(void) {

	//VARIABLES
	//setting up timer
	int timer=timerfd_create(CLOCK_MONOTONIC, 0);
	//unsigned int time;
	struct timespec endingT;
	gps Buffer;

	pthread_t pthread0;

	//int x=0;
	unsigned char buf= 0;

	int pipe_one;


	//to start GPS device without opening another terminal
	//there was a lot of trial and error to find this exact line of code below
	//doesn't need sudo since to start the program I use sudo ./Lab4_Main
	//by association since this comes after it doesn't need sudo just &

	
	//pipe1 open
	if((pipe_one =open("/tmp/N_pipe1", O_RDONLY))<0)
	{
		printf("\nN_pipe1 couldn't be opened Main\n");
		return EXIT_FAILURE;
	}


	//create thread
	pthread_create(&pthread0, NULL, (void*)Parthread, (void *)&Buffer);

	sleep(1);
	//getting starting time stamp. can't put in while loop since it would keep updating
	printf("\nPipe is open");
	clock_gettime(CLOCK_MONOTONIC, &startingT);
	//made this integer x loop a certain amount of times so I wouldn't have to Ctrl+C it to exit
	while(1)
	{
		
		usleep(250000);		

		if(read(pipe_one,&buf, sizeof(buf))<0)
		{
			printf("\nN_pipe1 read error Main\n");
			return EXIT_FAILURE;
		}
		else 
		{
			Buffer.loc=buf;
		}

		//getting the ending time stamp Pipe1
		clock_gettime(CLOCK_MONOTONIC, &endingT);

		//printing GPS Times ending-starting times
		printf("\nGPS Location: %u  GPS Time-Stamp, Seconds: %u NanoSeconds: %d", buf,(endingT.tv_sec-startingT.tv_sec),(endingT.tv_nsec-startingT.tv_nsec));
		Buffer.time_stampS=endingT.tv_sec-startingT.tv_sec;
		Buffer.time_stampN=endingT.tv_nsec-startingT.tv_nsec;

	}

	printf("\n");
	//this was deletes the pipe to restart timer, not needed
	//system("rm /tmp/N_pipe1");
	return EXIT_SUCCESS;
}
