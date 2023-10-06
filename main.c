/*
Written by Connor Watz
Main C file to run photogate laser subsystem, 
startup sequence, camera subsystem, and 
display subsystem.

The camera is not initialized here, but the output
value is read from "disp.txt"

*/

#include <stdio.h>
#include <unistd.h>
#include <pigpio.h>

/* Custom header files */
#include "dispDriver.h"
#include "startup.h"

#define BEAM1 7 
#define BEAM2 0
#define FILEPTR "disp.txt"

int calcSpeed(float t1, float t2, int stimp, int times[]);

/* -----------------------------------------------------------------------------------------------------------------
 * Speed Interrupt Routines
 *     
 *     These ISRs are triggered when one of the laser beams is broken. 
 *     They measure the velocity of a golf ball.
 *
 * -----------------------------------------------------------------------------------------------------------------*/

int flg = 0;

void beam1Time(int gpio, int level, uint32_t tick, void *inArray){
    
    int diff = 0;
    float dist = 0;
    int stimp = 10;
    float v = 0;
    int *times = inArray;
    times[0] = times[1];						// Shift time number over
    times[1] = tick;							// Record new time
    if(level == 0){							// Only calculate time if beam is constant
        diff = (times[1] - times[0]);
    }
    flg = 1;

    v = 1.680/(times[1] - times[0])*12*1000;					// Measure speed, a golf ball is 1.680 inches long 
    dist = (v)*(v)*(stimp/40.24);
    printf("Distance: %f ft\n", dist);
    return;
}

/* ----- This interrupt will only be inserted when 2nd photogate is set up
void beam2Time(int gpio, int level, uint32_t tick, void *inArray){
    
    int diff = 0;
    int *times = inArray;
    times[2] = times[3];						// Shift time number over
    times[3] = tick;							// Record new time

    if(level == 0){							// Only calculate time if beam is constant
        diff = (times[3] - times[2]);
    }
    flg = 1;
}
*/
/* --------------------------------------------------------------------------------------------------------------------*/

int main(void){
    startup();								// Run through startup phase
    int times[4] = {0,0,0,0};						// Timing array
    float dist;
    float s1, s2, st;							// Variables to store speed
    int stimp = 10;

/* Initialize PiGPIO daemon */    
    if (gpioInitialise() < 0){
	fprintf(stderr, "pigpio init failed\n");
	return 1;
    }
    gpioSetAlertFuncEx(BEAM1, beam1Time, times);			// Set callback for beam 1 pin
 //   gpioSetAlertFuncEx(BEAM2, beam2Time, times);			// Set callback for beam 2 pin

/* Main loop */
    while(1){
	    sendData(FILEPTR);  
    }
    return 0;
}


int calcSpeed(float t1, float t2, int stimp, int times[]){
    int dist = 0;
    t1 = 1.680/(times[1] - times[0])*12*1000;					// Measure speed, a golf ball is 1.680 inches long 
    t2 = 1.680/(times[3] - times[2])*12*1000;					// Speeds are all in ft/s
    printf("Most recent putt: \n"
           "%f ft/s\n"
           "%f ft/s\n", t1, t2);
    
    dist = (t1)*(t1)*(stimp/40.24);
    //dist = ((t1+t2)/2)*((t1+t2)/2)*(stimp/40.24);
    
    printf("Distance: %f\n", dist);
    return dist;
}
