
// Example 1
// 1. Forward/Backward
// 2. Point Turn Right/Left

#include <stdio.h>
#include <wiringPi.h>

#define IN1_PIN		1
#define IN2_PIN		4
#define IN3_PIN		5
#define IN4_PIN		6


void initDCMotor();
void goForward();
void goBackward();
void goLeft();
void goRight();
void stopDCMotor();

int cntr = 1;

int main(void)
{
	if(wiringPiSetup() == -1)
		return 0;
	
	pinMode(IN1_PIN, OUTPUT);
	pinMode(IN2_PIN, OUTPUT);
	pinMode(IN3_PIN, OUTPUT);
	pinMode(IN4_PIN, OUTPUT);
	
	initDCMotor();
	
	while(cntr>0)
	{
		   goForward();
		   delay(1000); //1 sec
          
		   stopDCMotor();
	       delay(500);
		 
	    	goBackward();
	        delay(500);
			
			stopDCMotor();
			delay(500);

			goRight();
			delay(500);

	        goLeft();
	        delay(500);
	        
	        stopDCMotor();
	        delay(1000);
	        
	        cntr--;
		    break;
	}
		
	return 0;
}


void initDCMotor()
{
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
	

//gcc 1-motor_A.c -o motora -lwiringPi
// ./motora