#include <stdio.h>

#include <wiringPi.h>
#include "wrappers/MoveFun.h"
#include "wrappers/UltraSonicFun.h"
#include "wrappers/IRSenFun.h"
#include "wrappers/LineTracersFun.h"

#define LEFT_90 1300

#define RIGHT_90 1152
#define _60_CM 1300

#define LEFT_TRACER_PIN 10
#define RIGHT_TRACER_PIN 11


void mission1();
void mission2();
void mission3();
void mission4();
void checkLineTracers();
void midterm();
void avoidObstacle(int coefLeft, int coefRight, int coefForward);

int main(void){

    //Validation
    if(wiringPiSetup() == -1){
        return 0;
    }

    //Test Area
    //mission1(); // move forward for 1 sec
    //mission2(); //forever meassure distance using ultrasonic sensor
    //mission3(); //forever meassure obstacles using IR sensers
    //mission4();

    checkLineTracers();
    //midterm();


    return 0;
}


void mission1(){

    int timesToLaunch = 1;

    while(timesToLaunch > 0){

        //Movement
        initPinMode();
        initDCMotorPWM();
        wSmoothLeft(LEFT_90);
        
        wSmoothRight(RIGHT_90);
        
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

void checkLineTracers(){
    initLineTacer();
    
    int leftTracer;
    int rightTracer;
  
    while (1) {
		 
	leftTracer = digitalRead(LEFT_TRACER_PIN);
	rightTracer = digitalRead(RIGHT_TRACER_PIN);
   
         if (leftTracer == 0 && rightTracer == 1) {
             printf("Left\n");  
             wFullStop(1000);    
            

         }else if (rightTracer ==0 && leftTracer == 1) {
               printf("Right\n");   
               wFullStop(1000);
            
                  
         }else if (rightTracer == 0 && leftTracer == 0) {
               printf("Both\n"); 
               initDCMotorPWM();
                wGoForwardPwm(1000);
                 
                  
                    
                               
         }else if (rightTracer == 1 && leftTracer == 1) {
              printf("No\n");   
              wFullStop(1000); 
            
         }     
	 }

    
}

void midterm(){

    //Initialize variables
    int timesToLaunch = 1;
    int distance = 0;
    int leftLineTracer = 0;
    int rightLineTracer = 0;


    // object Flags

    int firstObject = 1;
    int secondObject = 2;
    int thirdObject = 3;

    int objectsPassed= 0;
    int stillSeeObject = 0;

    // Movement coefficients

    int cForward = 500;
    int cLeft = 300;
    int cRight = 300;


    //Setup Actuators and Sensors
    initPinMode(); // Motor driver
    initUltrasonic(); // Ultrasonic
    initDCMotorPWM(); // Motor
    initLineTacer(); // LineTracers

    while(timesToLaunch){

        distance = getDistance();
        delay(100);
        printf("distance %dcm\n", distance);
        readLineTracers(&leftLineTracer, &rightLineTracer);


        if(distance < 15){
            // We got an object
            printf("See object on distance %dcm, taking maneuvers\n", distance);

            //Here we should check if some object was removed or not
            if(stillSeeObject != 1){
                objectsPassed++;
            }

            if(objectsPassed == firstObject){
                // We met a first object, car should stay until object will be removed
                printf("Inside firstObject\n");
                stillSeeObject = 1; 
                wFullStop(1000);
            }

            if(objectsPassed == secondObject){
                // we met a second object, car should avoid it
                printf("Inside secondObject\n");
                wFullStop(1000);
            }

            if(objectsPassed == thirdObject){
                // we met a third object, car should stop and terminate the process
                printf("Inside fthirdObject\n");
                wFullStop(1000);
                break;
            }



        }

        else{
            // We didnt meet any object, continue to move
            stillSeeObject = 0;

            if(leftLineTracer == 1 && rightLineTracer == 1){
                // means no white/yellow line in front of the car
                printf("leftLineTracer = %d, rightLineTracer = %d : Moving Forward in 0.5s", leftLineTracer, rightLineTracer);
                initDCMotorPWM();
                wGoForwardPwm(cForward);
            }
            else if(leftLineTracer == 1 && rightLineTracer == 0){
                printf("leftLineTracer = %d, rightLineTracer = %d : Moving Right", leftLineTracer, rightLineTracer);
                // car lost a yellow line on right side, required to move right

            }
            else if(leftLineTracer == 0 && rightLineTracer == 1){
                printf("leftLineTracer = %d, rightLineTracer = %d : Moving Left", leftLineTracer, rightLineTracer);
                // car lost a yellow line on left side, required to move left

            }
            else if(leftLineTracer == 0 && rightLineTracer == 0){
                printf("leftLineTracer = %d, rightLineTracer = %d : Stop", leftLineTracer, rightLineTracer);
                // car lost yellow lines on both sides, required to stop
                wFullStop(1000);
            }

        }

    }

}


void avoidObstacle(int coefLeft, int coefRight, int coefForward){
    wGoRight(coefRight);
    wGoLeft(coefLeft);
}
