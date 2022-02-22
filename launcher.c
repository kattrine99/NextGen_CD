#include <stdio.h>

#include <wiringPi.h>
#include "wrappers/MoveFun.h"

int cntr = 1;

int main(void){
    if(wiringPiSetup() == -1){
        return 0;
    }

    pinMode(IN1_PIN,OUTPUT);
    pinMode(IN2_PIN,OUTPUT);
    pinMode(IN3_PIN,OUTPUT);
    pinMode(IN4_PIN,OUTPUT);

    initDCMotor();

    while(cntr > 0){
        goForward();
        delay(500);
        cntr--;
    }

    return 0;
}