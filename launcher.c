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
    //mission2(); //forever meassure distance using ultrasonic sensor
    //mission3(); //forever meassure obstacles using IR sensers
    //mission5(); hw1


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

    while(timesToLaunch){

        distance = getDistance();

        if(distance < 30){
            //Stop car
            stopDCMotor();

        } else{
            //Continue to move
            initDCMotor();
            goForward();
            delay(1000);
        }
    }
}

void mission5(){
    int numberOfObjects = 4
    int distance = 0;

    initDCMotorPWM(); // Activate DC motor with PWM
    initUltrasonic(); // Activate UltraSonic sensor
    initIR(); // Activate IR sensor


    while(1){
        distance = getDistance();

        if(distance < 25){
            //Object A
            if(numberOfObjects==4){
                mission5AList1();
                numberOfObjects--;
            }

            //Object B
            if(numberOfObjects == 3){
                mission5AList2();
                numberOfObjects--;
            }


            //Object C
            if(numberOfObjects == 2 ){
                mission5AList2();
                numberOfObjects--;
            }


            //Object D
            if(numberOfObjects == 1){
                mission5AList3();
                numberOfObjects--;
                stopDCMotorPWM();

            }


        } else {
            //We did not get obstable continue
            wGoForward(400);
        }
        delay(100);
    }
}

void mission5AList1(){
    wSmoothRight(1000);
    wSmoothLeft(1000);
}

void mission5AList2(){
    wSmoothRight(1000);
    wGoLeft(500);
    wGoForward(1000);
    wSmoothLeft(1000);
}
void mission5AList3(){
    wSmoothRight(1000);
    wGoForward(1000);
}