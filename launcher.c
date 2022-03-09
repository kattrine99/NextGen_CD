#include <stdio.h>

#include <wiringPi.h>
#include "wrappers/MoveFun.h"
#include "wrappers/UltraSonicFun.h"
#include "wrappers/IRSenFun.h"
#include "wrappers/LineTracersFun.h"


#define LEFT_TRACER_PIN 10
#define RIGHT_TRACER_PIN 11

void checkLineTracers();
void midterm();
void avoidObstacle(int coefLeft, int coefRight, int coefForward);

int main(void){

    //Validation
    if(wiringPiSetup() == -1){
        return 0;
    }

    //Test Area
    wGoForwardPwm(1000);
    checkLineTracers();
    //midterm();


    return 0;
}




void checkLineTracers(){
    initLineTacer();
    
    int leftTracer;
    int rightTracer;
    initUltrasonic(); // Ultrasonic
    
  
    while (1) {
        
		 
	leftTracer = digitalRead(LEFT_TRACER_PIN);
	rightTracer = digitalRead(RIGHT_TRACER_PIN);
   
         if (leftTracer == 0 & rightTracer == 1) {
             printf("Left\n");  
                 wGoRightPWM(10);
                
             
             

         }else if (rightTracer ==0 & leftTracer == 1) {
               printf("Right\n");   
               wGoLeftPWM(10);
               
               
            
                  
         }else if (rightTracer == 0 & leftTracer == 0) {
               printf("Both\n"); 
               
                 wFullStop(100);
                  
                    
                               
         }else if (rightTracer == 1 & leftTracer == 1) {
              printf("No\n");   
               
              
              initDCMotorPWM();
                wGoForwardPwm(10);
            
         }     
	 }

    
}

void midterm(){

    //Initialize variables
    int timesToLaunch = 1;
    int distance = 0;
    int leftLineTracer;
    int rightLineTracer;


    // object Flags

    int firstObject = 1;
    int secondObject = 2;
    int thirdObject = 3;

    int objectsPassed= 0;
    int stillSeeObject = 0;

    // Movement coefficients

    int cForward = 500;
    int cLeft = 150;
    int cRight = 150;
    int cStop = 500;

    int dinamicCoefRight= (int)cRight * 1.00;
    int dinamicCoefLeft = (int)cLeft * 1.00;


    //Setup Actuators and Sensors
    initPinMode(); // Motor driver
    initUltrasonic(); // Ultrasonic
    initDCMotorPWM(); // Motor
    initLineTacer(); // LineTracers

    while(timesToLaunch){

        distance = getDistance();
        delay(100);
        printf("distance %dcm\n", distance);

        leftLineTracer = digitalRead(LEFT_TRACER_PIN);
        rightLineTracer = digitalRead(RIGHT_TRACER_PIN);
        
        
        
        stillSeeObject = 0;

            if(leftLineTracer == 1 && rightLineTracer == 1){
                // means no white/yellow line in front of the car
                printf("leftLineTracer = %d, rightLineTracer = %d : Stop", leftLineTracer, rightLineTracer);
            
                
                
            }
            else if(leftLineTracer == 1 && rightLineTracer == 0){
                printf("leftLineTracer = %d, rightLineTracer = %d : Moving Right", leftLineTracer, rightLineTracer);
                // car lost a yellow line on right side, required to move right
                wGoRightPWM(dinamicCoefRight);

            }
            else if(leftLineTracer == 0 && rightLineTracer == 1){
                printf("leftLineTracer = %d, rightLineTracer = %d : Moving Left", leftLineTracer, rightLineTracer);
                // car lost a yellow line on left side, required to move left
                wGoLeftPWM(dinamicCoefLeft);

            }
            else if(leftLineTracer == 0 && rightLineTracer == 0){
                // car lost yellow lines on both sides, required to move forward
                printf("leftLineTracer = %d, rightLineTracer = %d : Forward", leftLineTracer, rightLineTracer);
                initDCMotorPWM();
                wGoForwardPwm(cForward);
                
              

                

            }

        /*if(distance < 20){
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

                wFullStop(cStop);
            }

            if(objectsPassed == secondObject){
                // we met a second object, car should avoid it
                printf("Inside secondObject\n");
                avoidObstacle(cLeft, cRight, cForward);
                wFullStop(cStop);

            }

            if(objectsPassed == thirdObject){
                // we met a third object, car should stop and terminate the process
                printf("Inside fthirdObject\n");

                wFullStop(cStop);
                break;
            }*/



        }

        
            // We didnt meet any object, continue to move
            

        

    }




void avoidObstacle(int coefLeft, int coefRight, int coefForward){
    wGoRightPWM(coefRight);
    wGoForwardPwm(coefForward);
    wGoLeftPWM(coefLeft);
    wGoForwardPwm(coefForward);
    wGoLeftPWM(coefLeft);
    wGoForwardPwm(coefForward);
    wGoRightPWM(coefRight);
}
