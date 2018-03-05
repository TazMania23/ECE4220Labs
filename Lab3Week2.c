/*
 ============================================================================
 Name        : Lab3Week2.c
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

#include "ece4220lab3.h"

#define LEDR  8		//RED- Pedistrians
#define LEDY  9		//YELLOW Light 2
#define LEDG  7		//GREEN Light 1
#define LEDB 21		//Blue light only to define and shut off
//don't need button since thread is controlling red light
//Test results 1st Fifo then rr
#define SCHED_POLICY SCHED_FIFO

typedef struct{
	int ptl;
}priority;
//following example
pthread_mutex_t lock;

//one function for the each purpose thread
void greenLight(void *ptr)
{
	//variable to hold priority pointer
	priority *hold= (priority*)ptr;

	struct sched_param param;
	param.sched_priority= (*hold).ptl;
	sched_setscheduler(0, SCHED_POLICY, &param);

	while(1){

		pthread_mutex_lock(&lock);//locks

		printf("\nGreen Light"); //check
		//turn everything off first
		digitalWrite(LEDR,LOW);
		digitalWrite(LEDY,LOW);
		digitalWrite(LEDG,LOW);
		digitalWrite(LEDB,LOW);
		//then turn on Green light. This should happen quickly
		digitalWrite(LEDG,HIGH);

		sleep(1);

		pthread_mutex_unlock(&lock);

		usleep(1000);

	}
}

void yellowLight(void *ptr)
{
	//variable to hold priority pointer
		priority *hold= (priority*)ptr;

		struct sched_param param;
		param.sched_priority= (*hold).ptl;
		sched_setscheduler(0, SCHED_POLICY, &param);

		while(1){

			pthread_mutex_lock(&lock);//locks

			printf("\nYellow Light"); //check
			//turn everything off first
			digitalWrite(LEDR,LOW);
			digitalWrite(LEDY,LOW);
			digitalWrite(LEDG,LOW);
			digitalWrite(LEDB,LOW);
			//then turn on Yellow light. This should happen quickly
			digitalWrite(LEDY,HIGH);

			sleep(1);

			pthread_mutex_unlock(&lock);

			usleep(1000);

		}
}

void redLight(void *ptr)
{
	//variable to hold priority pointer
		priority *hold= (priority*)ptr;

		struct sched_param param;
		param.sched_priority= (*hold).ptl;
		sched_setscheduler(0, SCHED_POLICY, &param);

		while(1){

			pthread_mutex_lock(&lock);//locks

			printf("\nRed Light"); //check
			//turn everything off first
			digitalWrite(LEDR,LOW);
			digitalWrite(LEDY,LOW);
			digitalWrite(LEDG,LOW);
			digitalWrite(LEDB,LOW);
			//then turn on Red light. This should happen quickly
			digitalWrite(LEDR,HIGH);

			clear_button();

			sleep(1);

			pthread_mutex_unlock(&lock);

			usleep(1000);

		}
}


int main(int argc,char *argv[]) {

	if(argc!=4)
	{
		printf("\n---Wrong Number of Arguments---\n");
		return 0;
	}

	//collect priorities for each thread
	priority p1, p2, p3;
	p1.ptl=atoi(argv[1]);	//light 1 green light
	p2.ptl=atoi(argv[2]);	//light 2 yellow light
	p3.ptl=atoi(argv[3]);	//ped red light

	//checking can't be less than 0 or greater than 99
	if((p1.ptl || p2.ptl || p3.ptl) <0)
	{
		printf("Priority is less than 0 for one of the threads");
		return 0;
	}
	if((p1.ptl || p2.ptl || p3.ptl) >99)
	{
		printf("Priority is greater than 99 for one of the threads");
		return 0;
	}

	//setting up pins
	printf("Setting up Pins\n");
	wiringPiSetup();

	pinMode(LEDR, OUTPUT);
	pinMode(LEDY, OUTPUT);
	pinMode(LEDG, OUTPUT);
	pinMode(LEDB, OUTPUT);

	//setting/creating Threads
	pthread_t rLight, yLight, gLight;

	pthread_create(&gLight, NULL, (void*)greenLight, (void *)&p1);//green thread
	pthread_create(&yLight, NULL, (void*)yellowLight, (void *)&p2);//yellow thread
	pthread_create(&rLight, NULL, (void*)redLight, (void *)&p3);//red thread

	//joining
	pthread_join(rLight, NULL);
	pthread_join(yLight, NULL);
	pthread_join(gLight, NULL);

	return 0;
}
