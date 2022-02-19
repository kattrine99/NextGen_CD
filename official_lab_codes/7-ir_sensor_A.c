// IR Sensor + DCMotor
// Example 1

// Mission 1:
// If obstacle on left - turn right
// If obstacle on right - turn left
// if obstacle on both - stop


#include <stdio.h>
#include <wiringPi.h>


#define IN1_PIN		1
#define IN2_PIN		4
#define IN3_PIN		5
#define IN4_PIN		6

#define LEFT_IR_PIN 27
#define RIGHT_IR_PIN 26

void initIR();

void initDCMotor();
void goForward();
void goBackward();
void goLeft();
void goRight();
void stopDCMotor();

void mission1();

int main(void){
    
    if(wiringPiSetup() == -1)
	    return 0;
  
    int LValue, RValue; 
    initIR();
    initDCMotor();


    while (1) {
        
        LValue = digitalRead(LEFT_IR_PIN);
        RValue = digitalRead(RIGHT_IR_PIN);
        
        mission1(LValue, RValue);

       
    }
}


void initIR()
{
    pinMode(LEFT_IR_PIN, INPUT);
    pinMode(RIGHT_IR_PIN, INPUT);
		
}

void initDCMotor()
{
    	
	pinMode(IN1_PIN, OUTPUT);
	pinMode(IN2_PIN, OUTPUT);
	pinMode(IN3_PIN, OUTPUT);
	pinMode(IN4_PIN, OUTPUT);
	
	digitalWrite(IN1_PIN, HIGH);
	digitalWrite(IN2_PIN, HIGH);
	digitalWrite(IN3_PIN, HIGH);
	digitalWrite(IN4_PIN, HIGH);						
}

void goForward()
{
		digitalWrite(IN1_PIN, HIGH);
		digitalWrite(IN2_PIN, LOW);
		digitalWrite(IN3_PIN, HIGH);
		digitalWrite(IN4_PIN, LOW);		
		printf("Forward\n");
}	

void goBackward()
{
		digitalWrite(IN1_PIN, LOW);
		digitalWrite(IN2_PIN, HIGH);
		digitalWrite(IN3_PIN, LOW);
		digitalWrite(IN4_PIN, HIGH);		
		printf("Backwrad\n");
}	
	
	
void goLeft()
{
		digitalWrite(IN1_PIN, LOW);
		digitalWrite(IN2_PIN, HIGH);
		digitalWrite(IN3_PIN, HIGH);
		digitalWrite(IN4_PIN, LOW);		
		printf("Left\n");
}	

void goRight()
{
		digitalWrite(IN1_PIN, HIGH);
		digitalWrite(IN2_PIN, LOW);
		digitalWrite(IN3_PIN, LOW);
		digitalWrite(IN4_PIN, HIGH);		
		printf("Right\n");
}	

void stopDCMotor()
{
		digitalWrite(IN1_PIN, LOW);
		digitalWrite(IN2_PIN, LOW);
		digitalWrite(IN3_PIN, LOW);
		digitalWrite(IN4_PIN, LOW);		
		printf("Stop\n");
}	


void mission1(int LValue, int RValue){

     if(LValue == 1 && RValue == 0 ) {
            printf("Right\n");
            goRight();
            delay(600);
           
        }else if (LValue == 0 && RValue == 1) { 
            printf("Left\n");
            goLeft();
            delay(600);

        }else if(LValue == 0 && RValue == 0){
            printf("Stop\n");
            stopDCMotor();
            delay(600);

        }else if(LValue == 1 && RValue == 1){
            printf("Forward\n");
            goForward();
            delay(500);
        }

}


//gcc 7-ir_sensor_A.c -o ira -lwiringPi
// ./ira
