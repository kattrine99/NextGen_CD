// Ultrasonic
// Example 1
// 1. Keep the distance with object


#include <stdio.h>
#include <wiringPi.h>

#define TRIG_PIN		28
#define ECHO_PIN		29

#define IN1_PIN		1
#define IN2_PIN		4
#define IN3_PIN		5
#define IN4_PIN		6


void initUltrasonic();


void initDCMotor();
void goForward();
void goBackward();
void goLeft();
void goRight();
void stopDCMotor();
int getDistance();

int dist;

int main(void)
{
	if(wiringPiSetup() == -1)
		return 0;
	
    initUltrasonic();
    initDCMotor();
	
	while(1)
	{
        
	dist = getDistance();
	

        if(dist <= 15){
            stopDCMotor();
            printf("STOP: distance is less than 15cm\n");
            delay(500);
	    //break;

        } else{
		goForward();}
	
		
	}
	
	return 0;
}


void initUltrasonic(){
    pinMode(TRIG_PIN, OUTPUT);
	pinMode(ECHO_PIN, INPUT);

}

int getDistance()
{
	int 		start_time=0, end_time=0;
	float 	distance=0;

    digitalWrite(TRIG_PIN, LOW) ;
    delay(500) ;
    digitalWrite(TRIG_PIN, HIGH) ;
    delayMicroseconds(10) ;
    digitalWrite(TRIG_PIN, LOW) ;
    
    while (digitalRead(ECHO_PIN) == 0) ;
    start_time = micros() ;
    
    while (digitalRead(ECHO_PIN) == 1) ;
    end_time = micros() ;
    
    distance = (end_time - start_time) / 29. / 2. ;
	
	return (int)distance;
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



//gcc 5-ultrasonic_C.c -o ultrac -lwiringPi
// ./ultrac
