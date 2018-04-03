/*
 ============================================================================
 Name        : Lab4_Process2.c
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
#include <stdbool.h>
#include <sys/timerfd.h>
#include <stdint.h>
#include <time.h>

#include "ece4220lab3.h"

#define SCHED_POLICY SCHED_FIFO

int main(void) {
	//setting the button its just 27. added at last second
	wiringPiSetup();
	pinMode(27, INPUT);
	pullUpDnControl(27, PUD_DOWN);

	//PB is sending true or false
	bool PB;
	//int x = 0;
	//create pipe
	//send 1 if button is pushed else 0
	int pipe_two;
	system("mkfifo N_pipe2");
	fflush(stdout);
	//setting timer & period
	struct itimerspec itval;
	struct sched_param param;
	
	int timer = timerfd_create(CLOCK_MONOTONIC, 0);

	printf("\ntimer created");	


	param.sched_priority=55;
	sched_setscheduler(0,55,&param);


	//period 75ms
	itval.it_interval.tv_sec = 0;
	itval.it_interval.tv_nsec = 75000000;
	//timer nsec to delay it a tiny bit
	itval.it_value.tv_sec = 0;
	itval.it_value.tv_nsec = 1000;

	timerfd_settime(timer, 0, &itval, NULL);
	uint64_t numPeriods = 0;
	
	printf("\nProcess times set up\n");


	//opens pipe and check
	if ((pipe_two = open("N_pipe2", O_RDWR)) < 0) {
		printf("\nN_pipe2 couldn't be opened Process\n");
		return EXIT_FAILURE;
	}
	
	printf("\nPipe2 Didn't Fail");

	//while loop is set to 20 temporarily for it to work
	while (1) {
		if (check_button() == 1) {
			PB = TRUE;
			if(write(pipe_two, &PB, sizeof(PB)) != sizeof(PB))
			 {
				printf("\nN_pipe2 write error Process\n");
				return EXIT_FAILURE;
			}
			
			clear_button();
			printf("\nChecking Pushbutton");
			//sleep(1); to allow rapid fire

		}
		read(timer, &numPeriods, sizeof(numPeriods));
	//	printf("\nread is done");
	}

	return EXIT_SUCCESS;
}
