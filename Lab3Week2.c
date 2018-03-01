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

//#include "../Release/src/ece4220lab3.h"

#define LED1  8		//RED- Pedistrians
#define LED2  9		//YELLOW Light 2
#define LED3  7		//GREEN Light 1

#define PBUTTON  27

int check_button(void)
{

	return 0;
}
void clear_button(void)
{

}

int main(void) {

	wiringPiSetup();

	pinMode(LED1, OUTPUT);
	pinMode(LED2, OUTPUT);
	pinMode(LED3, OUTPUT);
	pinMode(PBUTTON, INPUT);

	pullUpDnControl(PBUTTON, PUD_DOWN);

	return 0;
}
