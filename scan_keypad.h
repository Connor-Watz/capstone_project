/* 
Written by Chase McGlinn
Read the input of the keypad

*/

#include <pigpio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define ROW1 27
#define ROW2 17
#define ROW3 4 
#define ROW4 3

#define COL1 11
#define COL2 9
#define COL3 10
#define COL4 22

#define GpioDelay 575000

char key[20][50];

int i, j;

int reset_flag = 0;
int start_flag = 0;
int stop_flag = 0;

char(*input(int index, FILE* fp))[50]
{ 
	int rowPins[4] = { ROW1, ROW2, ROW3, ROW4 };
	int colPins[4] = { COL1, COL2, COL3, COL4 };
	int keypad[4][4] = { {'1', '2', '3', 'P'}, {'4', '5', '6', 'E'}, {'7', '8', '9', 'R'}, {'*', '0', '#', 'D'} };

	char temp = '\0';
	strcpy(key[index], "");

	reset_flag = 0;
	start_flag = 0;
	stop_flag = 0;


	while (1)
	{

		for (i = 0; i < 4; i++)
		{

			for (j = 0; j < 4; j++)
			{

				gpioWrite(colPins[i], 0);



				if (gpioRead(rowPins[j]) == 0)
				{

					if (keypad[j][i] == 'E')
					{
						gpioDelay(GpioDelay);
						fprintf(fp, &key[index][0]);
						return key;
					}

					if (keypad[j][i] == 'D')
					{
						key[index][strlen(key[index]) - 1] = '\0';
						printf("After Delete: %s\n", &key[index][0]);
						temp = '\0';
						gpioDelay(GpioDelay);
					}
					else if (keypad[j][i] != 'E' && keypad[j][i] != 'R' && keypad[j][i] != 'D' && keypad[j][i] != 'P')
					{

						temp = (keypad[j][i]);

						strncat(key[index], &temp, 1);

						if (strlen(key[index]) > 3)
						{
							strcpy(key[index], &key[index][1]);
						}

						printf("Current Entry: %s\n", &key[index][0]);
						fprintf(fp, &key[index][0]);
						fclose(fp);

						//function to read and display data goes here

						fp = fopen("inputs.txt", "w");
						gpioDelay(GpioDelay);
					}


				}

			}
			gpioWrite(colPins[i], 1);



			if (reset_flag == 1)
			{
				strcpy(key[index], "Reset");
				fprintf(fp, &key[index][0]);
				gpioDelay(GpioDelay+200000);
				return key;

			}
			if (stop_flag == 1)
			{
				strcpy(key[index], "Start/Stop");
				fprintf(fp, &key[index][0]);
				gpioDelay(GpioDelay+200000);
				return key;
			}
		}
	}
}


int get_input(void)
{
	FILE* fp = fopen("inputs.txt", "w");
	int k = 0;
	while (1)
	{
		for (k = 0; k < 1; k++)
		{
			input(k, fp);
		}
		break;
	}
	fclose(fp);
	return 0;
}

int read_input(char entry_type[])
{
	FILE* fp = fopen("inputs.txt", "r");
	fgets(entry_type, 20, fp);
	fclose(fp);
	printf("User Entered: %s\n", entry_type);
	return 0;
}

void reset(int row, int level, uint32_t tick)
{
	gpioWrite(COL1, 1);
	gpioWrite(COL2, 1);
	gpioWrite(COL3, 1);

	if (gpioRead(ROW3) == 0)
	{
		//printf("%d, %d, %d\n", row, level, tick);
		//printf("------------Reset flag set------------\n");
		reset_flag = 1;
	}
	
	gpioDelay(200000);

}

void start_button(int row, int level, uint32_t tick)
{
	gpioWrite(COL1, 1);
	gpioWrite(COL2, 1);
	gpioWrite(COL3, 1);
	

	if(gpioRead(ROW1) == 0)
	{
		//printf("%d, %d, %d\n", row, level, tick);
		//printf("------------Start flag set------------\n");
		start_flag = 1;
		stop_flag = 1;
	}
	
	gpioDelay(200000);

}

void init_gpio(void)
{
	int i, j;
	int rowPins[4] = { ROW1, ROW2, ROW3, ROW4 };
	int colPins[4] = { COL1, COL2, COL3, COL4 };

	gpioInitialise();

	for (i = 0; i < 4; i++)
	{
		gpioSetMode(colPins[i], PI_OUTPUT);
		gpioWrite(colPins[i], 1);
	}

	for (j = 0; j < 4; j++)
	{
		gpioSetMode(rowPins[j], PI_INPUT);
		gpioSetPullUpDown(rowPins[j], PI_PUD_UP);

	}
	gpioSetAlertFunc(ROW3, reset);
	gpioSetAlertFunc(ROW1, start_button);
}
