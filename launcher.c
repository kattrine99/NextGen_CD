#include <stdio.h>

#include <wiringPi.h>
#include "wrappers/MoveFun.h"
#include "wrappers/UltraSonicFun.h"
#include "wrappers/IRSenFun.h"
#include "wrappers/LineTracersFun.h"

#define LEFT_90 800

#define RIGHT_90 900
#define _60_CM 1300


void mission1();
void mission2();
void mission3();
void mission4();
void mission6();
void mission7();

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
    //mission4();
    mission7();
    
    //stopDCMotor();


    return 0;
}


void mission1(){

    int timesToLaunch = 1;

    while(timesToLaunch > 0){

        //Movement
        initPinMode();
        initDCMotorPWM();
        wGoLeftPWM(100);
        delay(700);
        wGoForwardPwm(100);
        delay(1000);
        
        
        

        
        stopDCMotorPWM();
        stopDCMotor();
        break;
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
    int counter = 0;
    int smoothleft = 2300;
    while(timesToLaunch){

        distance = getDistance();
        delay(100);
        printf("distance %dcm\n", distance);
        
        if(counter == 2 | counter == 4 | counter == 6){
                counter ++;
                goForwardPWM();
                delay(_60_CM);
                
                wSmoothLeft(smoothleft);
                smoothleft  = smoothleft + 150 ;
                }
        
        
        if(distance < 30){
            //Stop car
            stopDCMotor();
            
            
            wSmoothRight(1300);
            goForwardPWM();
            delay(600);
            stopDCMotorPWM();
            stopDCMotor();
            wSmoothLeft(2100);
            
            
            counter = counter + 1;
                
            stopDCMotorPWM();
            
            

        } else{
            //Continue to move
            initDCMotorPWM();
            goForwardPWM();
            
        }
    }
}


void mission6()
{
    /*Misson Description

    A car will move continuosly forward while 
    does not detect a obstacle within a distance of 30 cm.
    After detection, car attempts to stop DC motors. As far 
    as obstacle will be removed a car continue to move forward.
    */

    //Initialize variables

    int timesToLaunch = 1;
    int distance = 0;
    int numberOfObjects = 4;

    //Setup Actuators and Sensors

    initPinMode();
    initUltrasonic();
    initDCMotorPWM();
    initIR();

    int leftIR = 0;
    int rightIR = 0;

    int counter = 0;
    int smoothleft = 2300;
    while(timesToLaunch){

        distance = getDistance();
        delay(100);
        printf("distance %dcm\n", distance);
        readIR(&leftIR, &rightIR);
        controlIR(leftIR,rightIR);

        
        
        if(distance < 30){
            //Stop car
            stopDCMotor();
            wGoRightPWM(RIGHT_90/2); //turn right on 45 degree
            goForwardPWM();
            delay(600);

            wGoLeftPWM(LEFT_90/2); // turn left on 45 degree, normalization

            if(leftIR == 1) { // means that we got an object from left side
                wGoForwardPwm(100);

            }
            else{ // means that we didn't get an object

                wSmoothLeft(2100);
                stopDCMotorPWM();
                stopDCMotor();
            }

            wSmoothLeft(2100);
            
            
            counter = counter + 1;
                
            stopDCMotorPWM();
            
            

        } else{
            //Continue to move
            initDCMotorPWM();
            goForwardPWM();
            
        }
    }
}



void mission7(){
    
    int timesToLaunch = 1;
    int distance = 0;
    int numberOfObjects = 4;

    //Setup Actuators and Sensors
    
    initPinMode();
    initUltrasonic();
    initDCMotorPWM();
    initIR();

    int leftIR = 0;
    int rightIR = 0;
    int stateIR = 0;

    int counter = 0;
    
    int right_time = 900
    
    
    while(timesToLaunch){
        
        distance = getDistance();
        delay(100);
        printf("distance %dcm\n", distance);
        readIR(&leftIR, &rightIR);
        controlIR(leftIR,rightIR);
        
        
        if (leftIR == 1 && rightIR == 0 && counter >= 2){
            delay(3000);
            
            
            wGoLeftPWM(LEFT_90);
            
            }
        
        if (counter == 5){
            delay(1000);
            wGoForwardPwm(3000);
            }
    
    
        if(distance < 20){
            
            stopDCMotorPWM();
            stopDCMotor();
            wGoRightPWM(right_time);
            counter++;
            if (counter == 1){
                wGoForwardPwm(1700);
            } else {
                wGoForwardPwm(1000);
            }
            
            wGoLeftPWM(right_time * 0.65);
            counter++;
            if (counter == 2){
                right_time += right_time/2
                }
            
            
            
        } else{
        //Continue to move
        initDCMotorPWM();
        goForwardPWM();
        }
    }
}




