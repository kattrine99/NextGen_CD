#include <stdio.h>

#include <wiringPi.h>
#include "wrappers/MoveFun.h"
#include "wrappers/UltraSonicFun.h"
#include "wrappers/IRSenFun.h"
#include "wrappers/LineTracersFun.h"


#define LEFT_TRACER_PIN 10
#define RIGHT_TRACER_PIN 11
#define LEFT_IR_PIN 27
#define RIGHT_IR_PIN 26
#define LEFT_IR_PIN 27
#define RIGHT_IR_PIN 26


void checkLineTracers();





int main(void){

    //Validation
    if(wiringPiSetup() == -1){
        return 0;
    }

    //Test Area
    initDCMotorPWM();
    wGoForwardPwm(1000);
    checkLineTracers();
   
    return 0;
}


void checkLineTracers(){
   
    float coof = 1;
    int right;
    int left;
    int distance;
    int leftTracer;
    int rightTracer;
    int counter = 0;
    
    initPinMode();
    initUltrasonic();
    initDCMotorPWM();
    initIR();
    initLineTacer();
    wGoForwardPwm(300);
    goForwardPWM();
    
    while (1) {
  
    left= digitalRead(LEFT_IR_PIN);
	  right = digitalRead(RIGHT_IR_PIN);

    distance = getDistance();
    printf("distance %dcm\n", distance);
      
	  leftTracer = digitalRead(LEFT_TRACER_PIN);
	  rightTracer = digitalRead(RIGHT_TRACER_PIN);
    
    
    if (distance < 15){

        counter++;
        if (counter == 1 | counter == 4){
            while(1){ 
                distance = getDistance();
                printf("fullstop");
                stopDCMotor();
                stopDCMotorPWM();
                delay(100);
                if(distance > 25){
                break;
                }
            }       
        initDCMotorPWM();
        goForwardPWM();
        } 
        
        if (counter == 2){
            int turns = 0;
            wGoRightPWM((int)(400*coof));
            while(1){
                rightTracer = digitalRead(RIGHT_TRACER_PIN);
                left= digitalRead(LEFT_IR_PIN);
                right = digitalRead(RIGHT_IR_PIN);
            
                printf("left %d, right %d\n",left,right);
                    if(turns == 55){
                        wFullStop(500);
                        initDCMotorPWM();
                        wGoRightPWM((int)(650*coof));
                        goto next;
                        }
                
                    if (rightTracer ==0 & leftTracer == 1) {
                        printf("Right\n");
                        wGoForwardPwm(10);   
                        wGoLeftPWM(10);
                        }
                    
                    else if(left == 0 && right == 1){
                        wGoLeftPWM((int)(20*coof));
                        wGoForwardPwm((int)(20*coof));
                        turns++;
                        }
                
                    else{
                        initDCMotorPWM();
                        wGoForwardPwm((int)(10*coof));
                        }
                } 
        }
        
        if (counter == 3){
              wGoForwardPwm((int)(200*coof));
                wFullStop((int)(1000*coof));
                wGoLeftPWM((int)(750*coof));
                wGoForwardPwm((int)(1600*coof));
                stopDCMotor();
                stopDCMotorPWM();
                break;
            }
    }

next:
         if (leftTracer == 0 & rightTracer == 1) {
             printf("Left\n");  
                 wGoRightPWM(10);

         }else if (rightTracer ==0 & leftTracer == 1) {
               printf("Right\n");   
               wGoLeftPWM(10);
                  
         }else if (rightTracer == 0 & leftTracer == 0  & (counter > 2 & counter !=4) ) {
               printf("Both\n"); 
                 wFullStop(100);
            
         }else if (rightTracer == 1 & leftTracer == 1) {
              printf("No\n");   
              initDCMotorPWM();
                wGoForwardPwm(10);
            
         }  
	 }
}