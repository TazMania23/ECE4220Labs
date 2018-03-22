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

#define SCHED_POLICY SCHED_FIFO
//for gps numbers
typedef struct{
	int loc;
	unsigned int time_stamp;
	int numPipe;
}gps;
//for process2 data
typedef struct{
	int prevLoc;
	unsigned int prevT;
	int afterLoc;
	unsigned int afterT;
	unsigned int nowT;
	int numPipe;
}location;

//add printing struct for extra credit

//Global Variable to share program starting time
struct timespec startingT;

void Parthread(void *ptr)
{
	gps *info= (gps *) ptr;
	pthread_t childT;

	//timers for start and timeP2 is recieved. Will get rid of startT
	struct timespec startT, timeP2;
	//pipe2 id
	int pipe_two;
	//my while loop while it's not infinity
	int x=0;
	//pipe2 is sending a Boolean
	bool PB=0;
	//pipe2 open
	if((pipe_two =open("N_pipe2", O_RDONLY))<0)
		{
			printf("\nN_pipe2 couldn't be opened Main\n");
		}
	//getting starting time for this thread
	clock_gettime(CLOCK_MONOTONIC, &startT);
	while(x<20)
	{
		if(read(pipe_two,&PB, sizeof(PB))<0)
		{
			printf("\nN_pipe2 read error Main\n");
		}
			//getting the time stamp Pipe2
			clock_gettime(CLOCK_MONOTONIC, &timeP2);

			//printing PushButton times just as a check before
			printf("\nPushbutton Time-Stamp: Seconds: %u NanoSeconds: %u", (timeP2.tv_sec-startT.tv_sec),(timeP2.tv_nsec-startT.tv_nsec));

			//creating child thread
			pthread_create(&childT, NULL, (void*)Kidthreads,(void *)info);
			x++;
	}
}

void Kidthreads(void *ptr)
{

}

int main(void) {

	//VARIABLES
	//setting up timer
	int timer=timerfd_create(CLOCK_MONOTONIC, 0);
	//unsigned int time;
	struct timespec endingT;



	int x=0;
	unsigned char buf= 0;

	int pipe_one;


	//to start GPS device without opening another terminal
	//there was a lot of trial and error to find this exact line of code below
	//doesn't need sudo since to start the program I use sudo ./Lab4_Main
	//by association since this comes after it doesn't need sudo just &
	system("./GPS_device &");
	system("./Lab4_Process2 &");

	sleep(1);
	//pipe1 open
	if((pipe_one =open("/tmp/N_pipe1", O_RDONLY))<0)
	{
		printf("\nN_pipe1 couldn't be opened Main\n");
		return EXIT_FAILURE;
	}




	//getting starting time stamp. can't put in while loop since it would keep updating
	clock_gettime(CLOCK_MONOTONIC, &startingT);

	//made this integer x loop a certain amount of times so I wouldn't have to Ctrl+C it to exit
	while(x<20)
	{
		//this slows the loop
		usleep(250000);

		if(read(pipe_one,&buf, sizeof(buf))<0)
		{
			printf("\nN_pipe1 read error Main\n");
			return EXIT_FAILURE;
		}
		//getting the ending time stamp Pipe1
		clock_gettime(CLOCK_MONOTONIC, &endingT);

		//printing GPS Times ending-starting times
		printf("\nGPS Location: %u  GPS Time-Stamp, Seconds: %u NanoSeconds: %u", buf,(endingT.tv_sec-startingT.tv_sec),(endingT.tv_nsec-startingT.tv_nsec));


		x++;
	}

	printf("\n");
	//close pipes
	close(pipe_one);

	//this was deletes the pipe to restart timer, not needed
	//system("rm /tmp/N_pipe1");
	return EXIT_SUCCESS;
}
