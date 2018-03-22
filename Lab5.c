/*
 ============================================================================
 Name        : Lab5.c
 Author      : Tsiania Hughes
 Version     :
 Copyright   : Your copyright notice: it's mine, Taz
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#define MSG_SIZE 40

//method to check the msg received from the client
int messageCheck(const char *msg)
{
	const char *mes1= 'WHOIS';
	const char *mes2= 'VOTE';
   if(strcmp(msg,mes1)==0)
	   return 1;
   else if(strcmp(msg,mes2)==0)
	   return 2;
   else
	   return 0;
}

int main(argc, *argv[]) {

	//check for right conditions
	if (argc!=2)
	{
		printf("\n Wrong amount of Arguments\n");
		return 0;
	}
	//setting up socket




	return EXIT_SUCCESS;
}
