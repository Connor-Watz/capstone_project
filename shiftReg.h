/*
Written by Connor Watz
This header file takes in an integer and
ouputs corresponding binary code to display 
a pattern for a 7-segment display.
Shift registers are used to minimize pins on 
the Raspberry Pi.

*/

#include <stdio.h>
#include <pigpio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define SRCLK 6					// SRCLR is on pin 20
#define RCLK  13
#define SER   5
#define SER2  16
#define SER3  20
#define TRAN1 19
#define TRAN2 26
#define TRAN3 21

void transmit(unsigned data_in1, unsigned data_in2, unsigned data_in3, int tran_cur, int tran_nxt, int ser, int ser2, int ser3);
void send(unsigned data_1, unsigned data_2, unsigned data_3,unsigned data_4 ,unsigned data_5,unsigned data_6,unsigned data_7,unsigned data_8,unsigned data_9, int ser, int ser2, int ser3);

// Convert individual integer numbers to specific binary code. 3 input integers split into 3 digits each

void display(int in1, int in2, int in3, int in4, int in5, int in6, int in7, int in8, int in9, int ser, int ser2, int ser3){
    unsigned out_1, out_2, out_3, out_4, out_5, out_6, out_7, out_8, out_9;
    switch(in1){
        case 0x0:
	    out_1 =0b011111101;
	    break;
	case 0x1:
	    out_1 =0b010100000;
	    break;
	case 0x2:
	    out_1 =0b011001111;
	    break;
	case 0x3:
	    out_1 =0b011101010;
	    break;
	case 0x4:
	    out_1 =0b010110010;
	    break;
	case 0x5:
	    out_1 =0b001111010;
	    break;
	case 0x6:
	    out_1 =0b001111110;
	    break;
	case 0x7:
	    out_1 =0b011100000;
	    break;
	case 0x8:
	    out_1 =0b011111110;
	    break;
	case 0x9:
	    out_1 =0b011111010;
	    break;
	default:
            out_1 =0b000000000;
	    break;
    }
    switch(in2){
        case 0x0:
	    out_2 =0b011111101;
	    break;
	case 0x1:
	    out_2 =0b010100000;
	    break;
	case 0x2:
	    out_2 =0b011001111;
	    break;
	case 0x3:
	    out_2 =0b011101010;
	    break;
	case 0x4:
	    out_2 =0b010110010;
	    break;
	case 0x5:
	    out_2 =0b001111010;
	    break;
	case 0x6:
	    out_2 =0b001111110;
	    break;
	case 0x7:
	    out_2 =0b011100000;
	    break;
	case 0x8:
	    out_2 =0b011111110;
	    break;
	case 0x9:
	    out_2 =0b011111010;
	    break;
	default:
	    out_2 =0b000000000;
	    break;
    }
    switch(in3){
        case 0x0:
	    out_3 =0b011111101;
	    break;
	case 0x1:
	    out_3 =0b010100000;
	    break;
	case 0x2:
	    out_3 =0b011001111;
	    break;
	case 0x3:
	    out_3 =0b011101010;
	    break;
	case 0x4:
	    out_3 =0b010110010;
	    break;
	case 0x5:
	    out_3 =0b001111010;
	    break;
	case 0x6:
	    out_3 =0b001111110;
	    break;
	case 0x7:
	    out_3 =0b011100000;
	    break;
	case 0x8:
	    out_3 =0b011111110;
	    break;
	case 0x9:
	    out_3 =0b011111010;
	    break;
	default:
	    out_3 =0b000000000;
	    break;
    }

    switch(in4){
        case 0x0:
	    out_4 =0b011111101;
	    break;
	case 0x1:
	    out_4 =0b010100000;
	    break;
	case 0x2:
	    out_4 =0b011001111;
	    break;
	case 0x3:
	    out_4 =0b011101010;
	    break;
	case 0x4:
	    out_4 =0b010110010;
	    break;
	case 0x5:
	    out_4 =0b001111010;
	    break;
	case 0x6:
	    out_4 =0b001111110;
	    break;
	case 0x7:
	    out_4 =0b011100000;
	    break;
	case 0x8:
	    out_4 =0b011111110;
	    break;
	case 0x9:
	    out_4 =0b011111010;
	    break;
	default:
            out_4 =0b000000000;
	    break;
    }
    switch(in5){
        case 0x0:
	    out_5 =0b011111101;
	    break;
	case 0x1:
	    out_5 =0b010100000;
	    break;
	case 0x2:
	    out_5 =0b011001111;
	    break;
	case 0x3:
	    out_5 =0b011101010;
	    break;
	case 0x4:
	    out_5 =0b010110010;
	    break;
	case 0x5:
	    out_5 =0b001111010;
	    break;
	case 0x6:
	    out_5 =0b001111110;
	    break;
	case 0x7:
	    out_5 =0b011100000;
	    break;
	case 0x8:
	    out_5 =0b011111110;
	    break;
	case 0x9:
	    out_5 =0b011111010;
	    break;
	default:
	    out_5 =0b000000000;
	    break;
    }
    switch(in6){
        case 0x0:
	    out_6 =0b011111101;
	    break;
	case 0x1:
	    out_6 =0b010100000;
	    break;
	case 0x2:
	    out_6 =0b011001111;
	    break;
	case 0x3:
	    out_6 =0b011101010;
	    break;
	case 0x4:
	    out_6 =0b010110010;
	    break;
	case 0x5:
	    out_6 =0b001111010;
	    break;
	case 0x6:
	    out_6 =0b001111110;
	    break;
	case 0x7:
	    out_6 =0b011100000;
	    break;
	case 0x8:
	    out_6 =0b011111110;
	    break;
	case 0x9:
	    out_6 =0b011111010;
	    break;
	default:
	    out_6 =0b000000000;
	    break;
    }

    switch(in7){
        case 0x0:
	    out_7 =0b011111101;
	    break;
	case 0x1:
	    out_7 =0b010100000;
	    break;
	case 0x2:
	    out_7 =0b011001111;
	    break;
	case 0x3:
	    out_7 =0b011101010;
	    break;
	case 0x4:
	    out_7 =0b010110010;
	    break;
	case 0x5:
	    out_7 =0b001111010;
	    break;
	case 0x6:
	    out_7 =0b001111110;
	    break;
	case 0x7:
	    out_7 =0b011100000;
	    break;
	case 0x8:
	    out_7 =0b011111110;
	    break;
	case 0x9:
	    out_7 =0b011111010;
	    break;
	default:
            out_7 =0b000000000;
	    break;
    }
    switch(in8){
        case 0x0:
	    out_8 =0b011111101;
	    break;
	case 0x1:
	    out_8 =0b010100000;
	    break;
	case 0x2:
	    out_8 =0b011001111;
	    break;
	case 0x3:
	    out_8 =0b011101010;
	    break;
	case 0x4:
	    out_8 =0b010110010;
	    break;
	case 0x5:
	    out_8 =0b001111010;
	    break;
	case 0x6:
	    out_8 =0b001111110;
	    break;
	case 0x7:
	    out_8 =0b011100000;
	    break;
	case 0x8:
	    out_8 =0b011111110;
	    break;
	case 0x9:
	    out_8 =0b011111010;
	    break;
	default:
	    out_8 =0b000000000;
	    break;
    }
    switch(in9){
        case 0x0:
	    out_9 =0b011111101;
	    break;
	case 0x1:
	    out_9 =0b010100000;
	    break;
	case 0x2:
	    out_9 =0b011001111;
	    break;
	case 0x3:
	    out_9 =0b011101010;
	    break;
	case 0x4:
	    out_9 =0b010110010;
	    break;
	case 0x5:
	    out_9 =0b001111010;
	    break;
	case 0x6:
	    out_9 =0b001111110;
	    break;
	case 0x7:
	    out_9 =0b011100000;
	    break;
	case 0x8:
	    out_9 =0b011111110;
	    break;
	case 0x9:
	    out_9 =0b011111010;
	    break;
	default:
	    out_9 =0b000000000;
	    break;
    }
    send(out_1, out_2, out_3,out_4, out_5, out_6, out_7, out_8, out_9, ser, ser2, ser3);
}

// Function to send binary data three times for 3 displays. Each cycle will utilize one display for each number 
// e.g first transmit is for the first digit of EACH number, second for second digit, etc.

void send(unsigned data_1, unsigned data_2, unsigned data_3,unsigned data_4 ,unsigned data_5,unsigned data_6,unsigned data_7,unsigned data_8,unsigned data_9, int ser, int ser2, int ser3){
    int i = 0;
    int j = 0;
    transmit(data_1, data_4, data_7, TRAN3, TRAN1, ser, ser2, ser3);
    transmit(data_2, data_5, data_8, TRAN1, TRAN2, ser, ser2, ser3); 
    transmit(data_3, data_6, data_9, TRAN2, TRAN3, ser, ser2, ser3);
    return;
}

// Feed binary data into shift register

void transmit(unsigned data_in1, unsigned data_in2, unsigned data_in3, int tran_cur, int tran_nxt, int ser, int ser2, int ser3){

    int curBit1, curBit2, curBit3 = 0;
    unsigned int mask = 0b100000000;							// Bit mask ensures only one digit is sent at a time
    for(int i = 0; i < 8; i++){
        curBit1 = data_in1 & mask;
	curBit2 = data_in2 & mask;
	curBit3 = data_in3 & mask;
	mask >>= 1;													// Shift bit mask right 1 (00001000 -> 00000100)
	if(curBit1 == 0){
	    gpioWrite(ser, 0);
	}
	else{
            gpioWrite(ser, 1);
	}
	if(curBit2 == 0){
	    gpioWrite(ser2, 0);
	}
	else{
            gpioWrite(ser2, 1);
	}
	if(curBit3 == 0){
	    gpioWrite(ser3, 0);
	}
	else{
            gpioWrite(ser3, 1);
	}
	usleep(5);													// 5 microsecond delay
	gpioWrite(SRCLK, 1);										// SRCLK cycle takes more time than write cycles (see data sheet for SN74HCS595 shift register)
	gpioWrite(SRCLK, 0);
	usleep(5);
	gpioWrite(ser, 0);
	gpioWrite(ser2, 0);
	gpioWrite(ser3, 0);
    }															// Repeat for 8 bits (1 for each 7 segment)
	
    gpioWrite(tran_cur, 0);										// Set current transistor to OFF
    usleep(5);
    gpioWrite(tran_nxt, 1);										// Turn next transistor ON
    gpioWrite(SRCLK, 1);										// Final clock cycle (pulse SRCLK and RCLK) sends correct bits to outputs
    gpioWrite(RCLK, 1);
    usleep(5);
    gpioWrite(SRCLK, 0);
    gpioWrite(RCLK, 0);
    usleep(5);
    return;
}


