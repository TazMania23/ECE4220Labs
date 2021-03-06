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
#include <math.h>
#include <time.h>
//to collect IP libraries
#include <ifaddrs.h>
#include <net/if.h>
#include <sys/ioctl.h>


#define MSG_SIZE 40
//Global Variables
char *My_IP;
int sockfd;

//method to check the msg received from the client
int messageCheck(const char *msg)
{
	//new lines were needed to make it work
	const char *mes1= "WHOIS\n";
	const char *mes2= "VOTE\n";
  if(strcmp(msg,mes1)==0)
	   return 1;
   else if(strcmp(msg,mes2)==0)
	   return 2;
   else
	   return 0;

}
void collectIP(void)
{
	//interface request
	struct ifreq myReq;
	myReq.ifr_addr.sa_family = AF_INET;

	snprintf( myReq.ifr_name, IFNAMSIZ, "wlan0" );
	ioctl( sockfd, SIOCGIFADDR, &myReq );	

	My_IP = inet_ntoa( ((struct sockaddr_in *)&myReq.ifr_addr)->sin_addr );
}

int main(int argc, char *argv[]) {
	
	srand(time(NULL));
	printf("\nStarting\n");
	//check for right conditions
	if (argc!=2)
	{
		printf("\n Wrong amount of Arguments. Expecting ./FileName PortNumber\n");
		return 0;
	}

	//Some Variables
	int PORT= atoi(argv[1]);
	char My_Message[MSG_SIZE]= "Taz on 128.206.19.15 is the master";
	char BCast[]="128.206.19.255";

	struct sockaddr_in server_addr, cli_addr;	
	int length=0;
	socklen_t Len= sizeof(struct sockaddr_in);
	int messCheck;
	int bindCheck;
	char Buffer[MSG_SIZE];


	//Creating Socket & Check
	sockfd= socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd<0)
	{
		printf("\nCreating Socket Error\n");
		return 0;
	}
	
	
//	printf("\nAfter Creating Socket\n");

	//Setting port and getting Length
	bzero(&server_addr, length);
//	printf("\nAfter bzero under Setting Port\n");

	server_addr.sin_family= AF_INET;
	server_addr.sin_port=htons(PORT);
	server_addr.sin_addr.s_addr= INADDR_ANY;

	length= sizeof(server_addr);
	
	//Binding Sockfd
        bindCheck=bind(sockfd, (struct sockaddr *)&server_addr,length);
        if(bindCheck<0)
        {
                printf("\nBinding Sockfd Error");
                return 0;
        }

//	printf("\nAfter Binding Socket\n");
	collectIP();
	//BroadCast setup
	cli_addr.sin_addr.s_addr=inet_addr(BCast);
	cli_addr.sin_port= htons(PORT);
//	printf("\nBroadCast\n");
	//Checking Set sock
	int val=1;
	if(setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &val, sizeof(val))<0)
	{
		printf("\nBroadCast Setup Error");
		return 0;
	}	

	
//------------------------------------------------------------------------
//While Loop
int Champ=0;
int randomNum;
unsigned int rNum;
unsigned int rIP;
unsigned int rAddr;

	while(1)
	{
		//based off of client_udp_broadcast.c
		bzero(Buffer,MSG_SIZE);
		
		int n;
		//receive Message
		n=recvfrom(sockfd,Buffer, MSG_SIZE, 0, (struct sockaddr *)&cli_addr, &Len);
		if(n<0)
		{
			printf("\nError Receiving Message");
			return 0;
		}
		//Successful Message Recieved
		printf("\nRecieved Message(Before Switch): %s\n", Buffer);

		//Message Check
		switch(messageCheck(Buffer))
		{	
			//Invalid Response or # symbol
			case 0:
				
				
				if(Buffer[0]=='#')
				{
					//printf("\n0\n");
					sscanf(My_IP, "%*u.%*u.%*u.%u %*u",&rAddr);
					//printf("\n1000000\n");
					sscanf(Buffer, "# %*u.%*u.%*u.%u %u", &rIP, &rNum);
					printf("\nRecieved Vote With => IP: %u\tNUM: %u\n", rIP,rNum);
					//to determine if I'm the champ
					if(rNum<randomNum)//if my num is greater
					{
						Champ= 1;
					}
					else if(rNum==randomNum)
					{
					//	printf("\nRnum %u RandomNum %u", rNum,randomNum);
					//	printf("\nrIP %u rAddr %u\n", rIP, rAddr);
						if(rIP>=rAddr)//compares the random generated numbers if equal
							Champ=0;
						else
							Champ=1;
					}
					else
					Champ=0;
				}
				
				break;
			//WHOIS
			case 1:
				//How to know if Im the master Check
				if(Champ==1)
				{
					puts("I am the Champion");
					char mast[MSG_SIZE];
					sprintf(mast, "%s",My_Message);
				
					sendto(sockfd, mast, MSG_SIZE, 0, (const struct sockaddr *)&cli_addr, Len);
				}
				break;
			//VOTE, recieves if I am master or not (change champ accordingly 
			case 2:
				
				//Generate Random NUM
				randomNum= rand()%10+1;
				//Check for feedback?
				char feedback[MSG_SIZE];
				
				sprintf(feedback, "# %s %d",My_IP,randomNum); 
				
				
				cli_addr.sin_addr.s_addr=inet_addr(BCast);
				n=sendto(sockfd, feedback, MSG_SIZE, 0, (struct sockaddr *)&cli_addr, Len);
				printf("\nSendto\n");
				//FeedBack Check
				if(n<0)
				{
					printf("\nError FeedBack Check (case 2)");
					return 0;
				}
				
				//recvfrom(sockfd, Buffer, MSG_SIZE, 0, (struct sockaddr *)&cli_addr, &Len);
				//printf("\nRecieved Message(In Switch): %s\n", Buffer);
				Champ=1;

				break;
			default:
				printf("\nIn Switch\n");
				break;
		}		


	}

	return EXIT_SUCCESS;
}	
