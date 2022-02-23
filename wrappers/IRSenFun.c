#include <stdio.h>
#include <wiringPi.h>
#include "IRSenFun.h"

#define LEFT_IR_PIN 27
#define RIGHT_IR_PIN 26

void initIR()
{
    pinMode(LEFT_IR_PIN, INPUT);
    pinMode(RIGHT_IR_PIN, INPUT);
		
}

void controlIR(int LValue, int RValue){

	if(LValue == 1 && RValue == 0 ) {
            printf("Right\n");
            //TODO smth
           
        }else if (LValue == 0 && RValue == 1) { 
            printf("Left\n");
            //TODO smth

        }else if(LValue == 0 && RValue == 0){
            printf("Stop\n");
            //TODO smth

        }else if(LValue == 1 && RValue == 1){
            printf("Forward\n");
            //TODO smth
        }	
}

void readIR(int* left, int* right){
	*left= digitalRead(LEFT_IR_PIN);
	*right = digitalRead(RIGHT_IR_PIN);
}

