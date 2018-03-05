/*
 ============================================================================
 Name        : Lab3Week1.c
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

#include "../Release/src/ece4220lab3.h"

#define LEDR  8		//RED- Pedistrians
#define LEDY  9		//YELLOW Light 2
#define LEDG  7		//GREEN Light 1
#define LEDB 21		//Blue light only to define and shut off
#define PBUTTON  27	//far Left
#define PBUTTON2 28 //far Right

//the single thread for the Null sequence. Polled only needs one
void Mainthread(void* ptr)
{
	printf("Polled Scheduling Commencing\n");
	//setting the thread priority higher
	struct sched_param param;
	param.sched_priority=51;
	sched_setscheduler(0,SCHED_FIFO, &param);

	//setting lights to off
	digitalWrite(LEDR,LOW);
	digitalWrite(LEDY,LOW);
	digitalWrite(LEDG,LOW);
	digitalWrite(LEDB,LOW);

	int *hold= (int*) ptr;

	printf("Starting Loop of Lights, Push right most button to end\n");

	while(digitalRead(PBUTTON2)==FALSE)
	{
		//Green
		digitalWrite(LEDG,HIGH);
		sleep(1);
		digitalWrite(LEDG,LOW);

		//Yellow
		digitalWrite(LEDY,HIGH);
		sleep(1);
		digitalWrite(LEDY,LOW);

		if(check_button()==1)
		{
			digitalWrite(LEDR, HIGH);
			clear_button();

			sleep(1);
			digitalWrite(LEDR,LOW);
		}
	}

}
int main(void) {
//setting up GPIO
	wiringPiSetup();

	pinMode(LEDR, OUTPUT);
	pinMode(LEDY, OUTPUT);
	pinMode(LEDG, OUTPUT);
	pinMode(LEDB, OUTPUT);
	pinMode(PBUTTON, INPUT);
	pinMode(PBUTTON2, INPUT);
//so button will be True until pushed
	pullUpDnControl(PBUTTON, PUD_DOWN);
	pullUpDnControl(PBUTTON2, PUD_DOWN);

	printf("Creating Threads\n");
	pthread_t Polled;
	int num=0;
	//creating the lone thread
	pthread_create(&Polled, NULL, (void*)Mainthread, (void*) &num);
	pthread_join(Polled, NULL);

	return 0;
}
