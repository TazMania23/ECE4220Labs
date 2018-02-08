/*
 ============================================================================
 Name        : Lab1Part1.c
 Author      : Tsiania Hughes
 Version     :
 Copyright   : Your copyright notice: it's mine, Taz
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>

//LEDs
#define LED1 8   //red
#define LED2 21 //blue
//Buttons
#define Button1 27
#define Button2 0
#define Button3 1
#define Button4 24
#define Button5 28
//the speaker I think
#define Speaker 22

int main(void) {
	
	wiringPiSetup();
	//setting up the pins 
	pinMode(LED1, OUTPUT);
	pinMode(LED2, OUTPUT);

	pinMode(Button1, INPUT);
	pullUpDnControl(Button1, PUD_DOWN);

	printf("Alternating LEDS between the Red and Blue Until Button1 is pushed\n");

	while(digitalRead(Button1)==FALSE)
	{
		digitalWrite(LED1,HIGH);//Led1 on
		sleep(1);
		digitalWrite(LED1,LOW);//Led1 off
		
		digitalWrite(LED2,HIGH);
		sleep(1);
		digitalWrite(LED2,LOW);
	}

	return 0;
}

