/*
 ============================================================================
 Name        : Lab4_Main.c
 Author      : Tsiania Hughes
 Version     :
 Copyright   : Your copyright notice: it's mine, Taz
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>             // standard symbolic constants and types (e.g. NULL); usleep
#include <wiringPi.h>   // needed for the wiringPi functions
#include <pthread.h>
#include <sched.h>
#include <sys/types.h>
#include <fcntl.h>

#include "ece4220lab3.h"

#define SCHED_POLICY SCHED_FIFO

int main(void) {
        unsigned char buf= malloc(sizeof(unsigned char))*8;
        unsigned char pipe_one;

        if((pipe_one =open("N_pipe1", O_RDONLY))<0)
        {
                printf("\nN_pipe1 couldn't be opened");
                return EXIT_FAILURE;
        }

        while(1)
        {
                sleep(1);
                if(read(pipe_one,&buf, sizeof(buf))<0)
                {
                        printf("\nN_pipe1 read error");
                        return EXIT_FAILURE;
                }

                printf("\nGPS Location: %u", buf);
        }
        close(pipe_one);
        return EXIT_SUCCESS;
}
