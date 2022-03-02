#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include "MoveFun.h"

#define IN1_PIN		1
#define IN2_PIN		4
#define IN3_PIN		5
#define IN4_PIN		6

#define MAX_SPEED 50
#define MIN_SPEED 0
#define SMOOTH_COOF 8


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
softPwmWrite(IN1_PIN, MAX_SPEED/SMOOTH_COOF);
softPwmWrite(IN2_PIN, MIN_SPEED);
softPwmWrite(IN3_PIN, MAX_SPEED);
softPwmWrite(IN4_PIN, MIN_SPEED);
}

void smoothRight() {
softPwmWrite(IN1_PIN, MAX_SPEED);
softPwmWrite(IN2_PIN, MIN_SPEED);
softPwmWrite(IN3_PIN, MAX_SPEED/SMOOTH_COOF);
softPwmWrite(IN4_PIN, MIN_SPEED);
}


void smoothBackLeft(){
softPwmWrite(IN1_PIN, MIN_SPEED);
softPwmWrite(IN2_PIN, MAX_SPEED/SMOOTH_COOF); 
softPwmWrite(IN3_PIN, MIN_SPEED);
softPwmWrite(IN4_PIN, MAX_SPEED);
}

void smoothBackRight(){
softPwmWrite(IN1_PIN, MIN_SPEED);
softPwmWrite(IN2_PIN, MAX_SPEED); 
softPwmWrite(IN3_PIN, MIN_SPEED);
softPwmWrite(IN4_PIN, MAX_SPEED/SMOOTH_COOF);
}

void initDCMotorPWM()
{
pinMode(IN1_PIN,SOFT_PWM_OUTPUT);
pinMode(IN2_PIN,SOFT_PWM_OUTPUT);
pinMode(IN3_PIN,SOFT_PWM_OUTPUT);
pinMode(IN4_PIN,SOFT_PWM_OUTPUT);
 
softPwmCreate(IN1_PIN, MIN_SPEED, MAX_SPEED);
softPwmCreate(IN2_PIN, MIN_SPEED, MAX_SPEED);
softPwmCreate(IN3_PIN, MIN_SPEED, MAX_SPEED);
softPwmCreate(IN4_PIN, MIN_SPEED, MAX_SPEED);
}

void goForwardPWM()
{	
softPwmWrite(IN1_PIN, MAX_SPEED);
softPwmWrite(IN2_PIN, MIN_SPEED);
softPwmWrite(IN3_PIN, MAX_SPEED);
softPwmWrite(IN4_PIN, MIN_SPEED);
}

void goBackwardPWM()	
{
softPwmWrite(IN1_PIN, MIN_SPEED);
softPwmWrite(IN2_PIN, MAX_SPEED);
softPwmWrite(IN3_PIN, MIN_SPEED);
softPwmWrite(IN4_PIN, MAX_SPEED);
}

void stopDCMotorPWM()
{
softPwmWrite(IN1_PIN, MIN_SPEED);
softPwmWrite(IN2_PIN, MIN_SPEED);
softPwmWrite(IN3_PIN, MIN_SPEED);
softPwmWrite(IN4_PIN, MIN_SPEED);		
printf("Stop\n");
}


// Wrapper functions for convinience

void wGoForwardPwm(int time){
	goForwardPWM();
	delay(time);
}	
void wGoBackwardPwm(int time){
	goBackwardPWM();
	delay(time);
}

void wSmoothRight(int time){
	smoothRight();
	delay(time);
}

void wSmoothLeft(int time){
	smoothLeft();
	delay(time);
}

void wGoRight(int time){
	goRight();
	delay(time);
}

void wGoLeft(int time){
	goLeft();
	delay(time);
}

void goRightPWM()
{
		digitalWrite(IN1_PIN, MAX_SPEED);
		digitalWrite(IN2_PIN, MIN_SPEED);
		digitalWrite(IN3_PIN, MIN_SPEED);
		digitalWrite(IN4_PIN, MAX_SPEED);		
		printf("RightPWM\n");
}

void wGoRightPWM(int time){
	goRightPWM();
	delay(time);
}

void goLeftPWM()
{
		digitalWrite(IN1_PIN, MIN_SPEED);
		digitalWrite(IN2_PIN, MAX_SPEED);
		digitalWrite(IN3_PIN, MAX_SPEED);
		digitalWrite(IN4_PIN, MIN_SPEED);		
		printf("LeftPWM\n");
}

void wGoLeftPWM(int time){
	goLeftPWM();
	delay(time);
}
