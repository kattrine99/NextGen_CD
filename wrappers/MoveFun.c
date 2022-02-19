#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

#define IN1_PIN		1
#define IN2_PIN		4
#define IN3_PIN		5
#define IN4_PIN		6

#define MAX_SPEED 50
#define MIN_SPEED 0

//official

void initDCMotor();

void goForward();
void goBackward();

void slow();

void goLeft();
void goRight();

void smoothLeft();
void smoothBackLeft();

void smoothRight();
void smoothBackRight();

void stopDCMotor();

//


//custom

void initPinMode();

//

void initPinMode(){
	pinMode(IN1_PIN, OUTPUT);
	pinMode(IN2_PIN, OUTPUT);
	pinMode(IN3_PIN, OUTPUT);
	pinMode(IN4_PIN, OUTPUT);
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

void slow(){
  
softPwmWrite(IN1_PIN, 30);
softPwmWrite(IN2_PIN, MIN_SPEED);
softPwmWrite(IN3_PIN, 30);
softPwmWrite(IN4_PIN, MIN_SPEED);

}

void smoothLeft() {
softPwmWrite(IN1_PIN, MAX_SPEED/8);
softPwmWrite(IN2_PIN, MIN_SPEED);
softPwmWrite(IN3_PIN, MAX_SPEED);
softPwmWrite(IN4_PIN, MIN_SPEED);
}

void smoothRight() {
softPwmWrite(IN1_PIN, MAX_SPEED);
softPwmWrite(IN2_PIN, MIN_SPEED);
softPwmWrite(IN3_PIN, MAX_SPEED/8);
softPwmWrite(IN4_PIN, MIN_SPEED);
}


void smoothBackLeft(){
softPwmWrite(IN1_PIN, MIN_SPEED);
softPwmWrite(IN2_PIN, MAX_SPEED/8); 
softPwmWrite(IN3_PIN, MIN_SPEED);
softPwmWrite(IN4_PIN, MAX_SPEED);
}

void smoothBackRight(){
softPwmWrite(IN1_PIN, MIN_SPEED);
softPwmWrite(IN2_PIN, MAX_SPEED); 
softPwmWrite(IN3_PIN, MIN_SPEED);
softPwmWrite(IN4_PIN, MAX_SPEED/8);
}
