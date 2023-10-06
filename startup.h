/* -------------------------------
Coded by Chase McGlinn, revised by Connor Watz
Program to run through startup sequence
Ask user for inputs, display input values, 
and store values for operation of the system.
---------------------------------- */


#include <pigpio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "scan_keypad.h"

#define setMode 2
#define enterStimp 18
#define targetDistLed 230
#define invalid 240
#define wait 12 
#define ready 73
#define mode1 100
#define mode2 100
#define mode3 100

int init;
char start_stop[] = "";
char mode[] = "";
int mode_int = 0;
char stimp[] = "";
char temp_stimp[] = "";
int stimp_int = 0;
char targetDist[] = "";
float f_targetDist = 0;

int i, j;

int startup(void)
{

// Initialization step: initialize gpio pins and set flags to 0

    init_gpio();
	
    gpioSetMode(setMode, PI_OUTPUT);						// Set GPIO mode to output for pin 1			
    gpioSetPullUpDown(setMode, PI_PUD_UP);					// Set pull up resistor on pin 1
    gpioWrite(setMode, 1);									// Pin 1 is set to 1

    gpioSetMode(enterStimp, PI_OUTPUT);
    gpioSetPullUpDown(enterStimp, PI_PUD_UP);
    gpioWrite(enterStimp, 0);

    gpioSetMode(wait, PI_OUTPUT);
    gpioSetPullUpDown(setMode, PI_PUD_UP);
    gpioWrite(wait, 1);

    gpioSetMode(ready, PI_OUTPUT);
    gpioSetPullUpDown(setMode, PI_PUD_UP);
    gpioWrite(ready, 0);

	int finished = 0;
	reset_flag = 0;
	stop_flag = 0;
	while (finished == 0)
	{
		reset_flag = 0;
		stop_flag = 0;
		

		gpioWrite(COL4, 0);									// Input from 'scan_keypad.h', read column 4
		gpioWrite(COL3, 1);
		gpioWrite(COL2, 1);
		gpioWrite(COL1, 1);

		printf("Press Start:\n");							// Terminal print for debugging purposes
		get_input();
		read_input(start_stop);

		if (start_flag == 1)
		{
			stop_flag = 0;
			gpioWrite(setMode, 0);
			gpioWrite(enterStimp, 1);

			printf("Enter Mode:\n");
			get_input();
			read_input(mode);
			mode_int = atoi(mode);

			//Checking reset and start/stop flags-----------------------------
			if (reset_flag == 1)
			{
				reset_flag = 0;
				break;
			}
			if (stop_flag == 1)
			{
				stop_flag = 0;
				exit(0);
			}
			//---------------------------------------------------------------

			switch (mode_int)
			{
			case 1:									//Mode 1
				printf("Enter Stimp:\n");
				get_input();
				read_input(stimp);

					

				stimp_int = atoi(stimp);
				printf("The stimp is %d\n", stimp_int);

				//Checking reset and start/stop flags-----------------------------
				if (reset_flag == 1)
				{
					reset_flag = 0;
					break;
				}

				if (stop_flag == 1)
				{
					stop_flag = 0;
					exit(0);
				}
				//---------------------------------------------------------------

				if (stimp_int > 15 || stimp_int < 4)
				{
					printf("Invalid Entry\n");
				}
				else
				{
					break;
				}

			case 2:									//Mode 2
				printf("Enter Stimp:\n");
				get_input();
				read_input(stimp);
				stimp_int = atoi(stimp);
				//Checking reset and start/stop flags-----------------------------
				if (reset_flag == 1)
				{
					reset_flag = 0;
					break;
				}
				if (stop_flag == 1)
				{
					stop_flag = 0;
					exit(0);
				}
				//---------------------------------------------------------------
				if (stimp_int > 15 || stimp_int < 4)
				{
					printf("Invalid Entry\n");
				}
				else
				{
					printf("Enter target distance:\n");
					get_input();
					read_input(targetDist);
					//Checking reset and start/stop flags-----------------------------
					if (reset_flag == 1)
					{
						reset_flag = 1;
						break;
					}

					if (stop_flag == 1)
					{
						stop_flag = 0;
						exit(0);
					}
					//---------------------------------------------------------------

					f_targetDist = atof(targetDist) * .1;
					printf("Target Distance = %.1f\n", f_targetDist);
					if (f_targetDist < 5 || f_targetDist > 100)
					{
						printf("Invalid Entry\n");
					}
					else
					{
						break;
					}
				break;
				}


			case 3:									//Mode 3
				printf("Enter Stimp:\n");
				get_input();
				read_input(stimp);
				stimp_int = atoi(stimp);
				

				//Checking reset and start/stop flags-----------------------------
				if (reset_flag == 1)
				{
					reset_flag = 0;
					break;
				}

				if (stop_flag == 1)
				{
					stop_flag = 0;
					exit(0);
				}
				//---------------------------------------------------------------
				if (stimp_int > 15 || stimp_int < 4)
				{
					printf("Invalid Entry\n");
					break;
				}
				finished = 1;


			default:
				//Checking reset and start/stop flags-----------------------------
				if (reset_flag == 1)
				{
					reset_flag = 0;
					break;
				}

				if (stop_flag == 1)
				{
					stop_flag = 0;
					exit(0);
				}
				//---------------------------------------------------------------
				printf("Invalid Entry\n");
			}

		}
		else
		{
		printf("Error: Invalid Entry\n");
		}
            break;
	}
	//startup();
	gpioTerminate();
}
