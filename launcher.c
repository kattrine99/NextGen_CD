#include <stdio.h>

#include <wiringPi.h>
#include "wrappers/MoveFun.h"
#include "wrappers/UltraSonicFun.h"
#include "wrappers/IRSenFun.h"


void mission1();
void mission2();
void mission3();

int main(void){

    //Validation
    if(wiringPiSetup() == -1){
        return 0;
    }

    //Test Area
    //mission1(); // move forward for 1 sec
    //mission2(); //forever meassure distance using ultrasonic sensor
    //mission3(); //forever meassure obstacles using IR sensers


    return 0;
}


void mission1(){

    int timesToLaunch = 1;

    while(timesToLaunch > 0){

        //Movement
        initPinMode();
        initDCMotor();
        goForward();
        delay(1000);
        stopDCMotor();
        timesToLaunch--;
    }
}

void mission2(){

    int timesToLaunch = 1;

    while(timesToLaunch>0){

        //UltraSonic
        initUltrasonic();
        getDistance();
        printf("distance %dcm\n", getDistance());
        delay(100);
    }

}

void mission3(){
    int timesToLaunch = 1;

    while(timesToLaunch>0){

        //IR sensors
        int LValue, RValue; 
        initIR();
        readIR(&LValue,&RValue);
        controlIR(LValue,RValue);
    }
}