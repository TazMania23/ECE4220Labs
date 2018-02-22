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

#define MY_PRIORITY 51  // kernel is priority 50

/*int main(void){
// --- Configure Timer ---
    int timer_fd = timerfd_create(CLOCK_MONOTONIC, 0);	// returns a file descriptor
		// Always good to check for errors. Look for timerfd_create()

	struct itimerspec itval;	// structure to hold period and starting time
    // timer fires every ## sec, ## nsec
    itval.it_interval.tv_sec = 0;		// check the data type
    itval.it_interval.tv_nsec = 0;	// check the data type

    // Timer will start in ## sec, ## nsec from the moment the timer is started
    itval.it_value.tv_sec = 0;		// check the data type
    itval.it_value.tv_nsec = 1;		// check the data type

	// start the timer (you need the file descriptor and itval structure above)
	timerfd_settime(timer_fd, 0, &itval, NULL);	// this function has a return value
		// Always good to check for errors. Look for timerfd_settime()


// --- Initialize current thread as RT task ---
	struct sched_param param;
    // Declare ourselfhow many periods it's been since you last checked in
    read(timer_fd, &nu as a real time task by elevating our priority
	// and setting an appropriate scheduling policy.
	param.sched_priority = MY_PRIORITY;
	sched_setscheduler(0, SCHED_FIFO, &param);	// this function has a return value
		// Always good to check for errors. Look for sched_setscheduler()


// --- Wait for the timer to expire ---
	uint64_t num_periods = 0;
	// The following is typically inside a loop. It will wait whatever is left of the
	// current period.
	// read tells you how many periods it's been since you last checked in
    read(timer_fd, &num_periods, sizeof(num_periods));	// this function has a return value
		// Always good to check for errors. Look for read()
    if(num_periods > 1) {
        puts("MISSED WINDOW");
        exit(1);
    }
    else
    	puts("Right");
    return 0;
}
*/
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
	
	int timer=timerfd_create(CLOCK_MONOTONIC, 0);
	char holdline[100];
	struct itimerspec itval;
	struct sched_param param;
	
	param.sched_priority = RT_Prority;
	sched_setscheduler(0, SCHED_FIFO, &param);
	//holding the struct pointer
	Just_Once *hold= (hold*)ptr;
	
	itval.it_interval.tv_sec= hold->period_s;
	itval.it_interval.tv_sec= hold->period_n;
	
	itval.it_interval.tv_sec= hold->start_s;
	itval.it_interval.tv_sec= hold->start_n;
	
	timerfd_settime(timer, 0, &itval, NULL);
	
	uint64_t numPeriods=0;
	//1 period pause
	read(timer, &numPeriods, sizeof(numPeriods));
	int x=0;
	while(x<20)
	{
		strcpy(hold->lyrics[x],holdline);
		read(timer, &numPeriods, sizeof(numPeriods));
	}
	
	if(numPeriods>1)
	{
		printf("\n-----Missed-----");
		exit(1);
	}
	

}
//Where the two threads will be created
void MultiThreads(void *ptr){
	
	// timer setup
	int timer=timerfd_create(CLOCK_MONOTONIC, 0);
	char holdline[100];
	struct itimerspec itval;
	struct sched_param param;
	
	param.sched_priority = RT_Prority;
	sched_setscheduler(0, SCHED_FIFO, &param);
	//holding the struct pointer
	basic *hold= (hold*)ptr;
	
	itval.it_interval.tv_sec= hold->period_s;
	itval.it_interval.tv_sec= hold->period_n;
	
	itval.it_interval.tv_sec= hold->start_s;
	itval.it_interval.tv_sec= hold->start_n;
	
	//opening file
	File *fptr;
	if(fptr=fopen(hold->fname,"r"))==NULL)
	{
		printf("\nFailed to Open File %s", hold->fname);
		exit(1); //exit fail =1
	}
	
	timerfd_settime(timer, 0, &itval, NULL);
	
	uint64_t numPeriods=0;
	//1 period pause
	read(timer, &numPeriods, sizeof(numPeriods));
	
	while(!feof(fptr))
	{
		//finish fscanf
		fscanf(fptr, "%s", holdline);
		read(timer, &numPeriods, sizeof(numPeriods));
	}
	fclose(fptr);
	
	if(numPeriods>1)
	{
		printf("\n-----Missed-----");
		exit(1);
	}
	
}


int main(argc, *argv[])
{
	//looping variable
	int x=0;
	//getting all the information needed to run
	Basic vfirst ={1, 0,100000, 0, 400000, "first.txt"};
	Basic vsecond={2, 0,300000, 0, 400000, "second.txt"};
	Just_Once vthird ={3,0 200000, 0, 200000, "Blank"};
	
	pthread_t thread1,thread2,thread3;
	//thread 1 & 2 go to the multithreads and thread 3 goes to sum
	pthread_create(&thread1, NULL,(void *)&MultiThreads, (void *)&vfirst);
	pthread_create(&thread2, NULL,(void *)&MultiThreads, (void *)&vsecond);
	pthread_create(&thread3, NULL,(void *)&Sumthread, (void *)&vthird);

	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	pthread_join(thread3,NULL);
//print out the song
	for(x=0;x<20;x++)
	{
		printf("Line %d: %s", x,vthird[x]);	
	}
	
	return 0;
}
