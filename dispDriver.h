/*

Written by Connor Watz
Break integer numbers into individual
digits. Flashes displays regularly to avoid
blank digits on 7-segment displays.


*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pigpio.h>
#include "shiftReg.h"

#define SRCLK 6					
#define RCLK  13
#define SER   5
#define SER2  16
#define SER3  20

#define TRAN1 19						// Transistors to cycle between individual displays
#define TRAN2 26
#define TRAN3 21


void initialize(void);

int sendData(char* filePtr){
    initialize();
    FILE *fp;
    int num1, num2, num3, tempNum;
    int num4, num5, num6, num7, num8, num9 = 0;
    char num[50];
    int i = 0;
	fp = fopen(filePtr, "r");
	if(fp == NULL){
	    printf("No File exists dumbass\n");
	    exit(1);
	    return 1;
	}
	fscanf(fp, "%s", &num);
	fclose(fp);
        tempNum = atoi(num);	
	if (tempNum < 10){
	    num1 = 10;
	    num2 = num[0]-48;
	    if(num[2] == NULL){num3 = 0;}
	    else{num3 = num[2] - 48;}
	}
	else{
            num1 = num[0]-48;
	    num2 = num[1]-48;
            if(num[3] == NULL){num3 = 0;}
	    else{num3 = num[3] - 48;}
	}
	do{
	    display(num1,num2,num3,num4, num5, num6, num7, num8, num9, SER, SER2, SER3); 
	    //display(num1+1,num2+1,num3+1,SER2);
	    //display(num1+2,num2+2,num3+2,SER3);

            i++;
	}
	while(i < 1000);
    return 0;
}


void initialize(void){

    if (gpioInitialise() < 0){
	fprintf(stderr, "pigpio initialize failed\n");
	return;
    }
    gpioSetMode(SRCLK, PI_OUTPUT);
    gpioSetPullUpDown(SRCLK, PI_PUD_UP);
    gpioWrite(SRCLK, 0);
    gpioSetMode(RCLK, PI_OUTPUT);
    gpioSetPullUpDown(RCLK, PI_PUD_UP);
    gpioWrite(RCLK, 0);
    gpioSetMode(SER, PI_OUTPUT);
    gpioSetPullUpDown(SER, PI_PUD_UP);
    gpioWrite(SER, 0);
    gpioSetMode(TRAN1, PI_OUTPUT);
    gpioWrite(TRAN1, 0);
    gpioSetMode(TRAN2, PI_OUTPUT);
    gpioWrite(TRAN2, 0);
    gpioSetMode(TRAN3, PI_OUTPUT);
    gpioWrite(TRAN3, 0);

    return;

}
