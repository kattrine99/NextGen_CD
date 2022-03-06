#include <stdio.h>
#include <wiringPi.h>
#include "LineTracersFun.h"


#define LEFT_TRACER_PIN 10
#define RIGHT_TRACER_PIN 11

void initLineTacer(){
	pinMode(LEFT_TRACER_PIN, INPUT);
	pinMode(RIGHT_TRACER_PIN, INPUT);		
}

void lineTracerDetect(int leftTracer, int rightTracer){
	
	
	
	if (leftTracer == 0 && rightTracer == 1) {
            printf("Right\n");
			//goRight();
			//delay(500);


        }
        else if (rightTracer == 0 && leftTracer == 1) {
            printf("Left\n");
			//goLeft();
			//delay(500);


        }
        else if (rightTracer == 0 && leftTracer == 0) {
            printf("Stop\n");
			//stopDCMotor();
			//delay(1000);
			

        }
        else if (rightTracer == 1 && leftTracer == 1) {
            printf("Forward\n");
			//goForward();
			//delay(500);

        }
	
	}

void readLineTracers(int* left, int* right){
	*left= digitalRead(LEFT_TRACER_PIN);
	*right = digitalRead(RIGHT_TRACER_PIN);
}
