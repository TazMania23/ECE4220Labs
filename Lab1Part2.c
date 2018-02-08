/*
 ============================================================================
 Name        : Cproject.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
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

#define Button1 27
#define Button2 0
#define Button3 1
#define Button4 24
#define Button5 28

#define Speaker 22

int main(void)
{

		wiringPiSetup();

		pinMode(LED1, OUTPUT);
		pinMode(Button1, INPUT);
		pinMode(Button2, INPUT);
		pinMode(Button3, INPUT);
		pinMode(Button4, INPUT);
		pinMode(Button5, INPUT);
		pinMode(Speaker, OUTPUT);

		pullUpDnControl(Button1, PUD_DOWN);
		pullUpDnControl(Button2, PUD_DOWN);
		pullUpDnControl(Button3, PUD_DOWN);
		pullUpDnControl(Button4, PUD_DOWN);
		pullUpDnControl(Button5, PUD_DOWN);
		pullUpDnControl(Speaker, PUD_DOWN);

		int butNum=0;
		int x;
	printf("Choose button 1-5\nGot 5 seconds to make it happen\n");
	while(1)
	{
		printf("Number: ");
		scanf("%d",&butNum);
		getchar();
		
		switch (butNum){

			case 1:
				while(1){
					 if(digitalRead(Button1)==TRUE)
						{
							for(x=0;x<1000;x++)
							{
								digitalWrite(Speaker, HIGH);
								usleep(450);
								digitalWrite(Speaker, LOW);
								usleep(450);
							}
						}
					}
				break;

			case 2:
				while(1){
					 if(digitalRead(Button2)==TRUE)
						
							for(x=0;x<1000;x++)
							{
								digitalWrite(Speaker, HIGH);
								usleep(500);
								digitalWrite(Speaker, LOW);
								usleep(500);
							}
					}
				break;

			case 3:
				while(1){
					 if(digitalRead(Button3)==TRUE)
						
							for(x=0;x<1000;x++)
							{
								digitalWrite(Speaker, HIGH);
								usleep(450);
								digitalWrite(Speaker, LOW);
								usleep(450);
							}
					}
				break;

			case 4:
				while(1){
					 if(digitalRead(Button4)==TRUE)
						
							for(x=0;x<1000;x++)
							{
								digitalWrite(Speaker, HIGH);
								usleep(500);
								digitalWrite(Speaker, LOW);
								usleep(500);
							}
					}
				break;

			case 5:
				while(1){
					if(digitalRead(Button5)==TRUE)
						
							for(x=0;x<1000;x++)
							{
								digitalWrite(Speaker, HIGH);
								usleep(450);
								digitalWrite(Speaker, LOW);
								usleep(450);
							}
					}
				break;

			default:
				printf("Whelp, nothing is going to happen if you hit the wrong buttonl\n");


		}
	}

	return 0;
}

