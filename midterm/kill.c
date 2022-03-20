#include <stdio.h>
#include <wiringPi.h>
#include "wrappers/MoveFun.h"

int main(void){

    //Validation
    if(wiringPiSetup() == -1){
        return 0;
    }

    
    
    stopDCMotorPWM();
	stopDCMotor();


    return 0;
}
