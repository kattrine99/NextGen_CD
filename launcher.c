#include <stdio.h>

#include <wiringPi.h>
#include "wrappers/MoveFun.h"
#include "wrappers/UltraSonicFun.h"
#include "wrappers/IRSenFun.h"
#include "wrappers/LineTracersFun.h"


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
    mission2(); //forever meassure distance using ultrasonic sensor
    //mission3(); //forever meassure obstacles using IR sensers
    //mission5(); hw1
    //mission4();
    
    //stopDCMotor();


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

void mission4(){

    /*Misson Description

    A car will move continuosly forward while 
    does not detect a obstacle within a distance of 30 cm.
    After detection, car attempts to stop DC motors. As far 
    as obstacle will be removed a car continue to move forward.
    */

    //Initialize variables

    int timesToLaunch = 1;
    int distance = 0;

    //Setup Actuators and Sensors

    initPinMode();
    initUltrasonic();
    initDCMotorPWM();

    while(timesToLaunch){

        distance = getDistance();
        printf("distance %dcm\n", distance);

        if(distance < 40){
            //Stop car
            stopDCMotor();
            delay(100);
            wSmoothRight(1000);
            goForwardPWM();
            delay(1000);
            stopDCMotorPWM();
            wSmoothLeft(2000);
            stopDCMotorPWM();
            
            

        } else{
            //Continue to move
            initDCMotorPWM();
            goForwardPWM();
            delay(100);
        }
    }
}




