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
void Sumthread(void *ptr){

}

void MultiThreads(void *ptr){

}

int main(argc, *argv[])
{

	pthread_t thread1,thread2,thread3;
	int var1=0,var2=0,var3=0;

	pthread_create(&thread1, NULL,(void *)&MultiThreads, (void *)&var1);
	pthread_create(&thread2, NULL,(void *)&MultiThreads, (void *)&var2);
	pthread_create(&thread3, NULL,(void *)&Sumthread, (void *)&var3);

	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	pthread_join(thread3,NULL);




	return 0;
}
