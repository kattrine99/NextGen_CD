
//Motor + Ultrasonic + Line Tracer

#include <stdio.h>
#include <wiringPi.h>
#include <stdbool.h>

#define LEFT_TRACER_PIN 10
#define RIGHT_TRACER_PIN 11


#define IN1_PIN		1
#define IN2_PIN		4
#define IN3_PIN		5
#define IN4_PIN		6

#define TRIG_PIN		28
#define ECHO_PIN		29

void initLineTacer();
void initDCMotor();
void goForward();
void goBackward();
void goLeft();
void goRight();
void stopDCMotor();

void initUltrasonic();
void lineTracerDetect();
int getDistance();

int dist;
int leftTracer;
int rightTracer;
bool test1;

int main(void) {

    if (wiringPiSetup() == -1)
        return 0;

    initLineTacer();
    initUltrasonic();
    initDCMotor();
    test1 = false;

    
    while (1) {

       
	
	dist = getDistance();
	

        if(dist <= 15){
            stopDCMotor();
            printf("STOP: distance is less than 15cm\n");
            delay(1000);
	    

        } else{
		lineTracerDetect();
		
		if(test1==true){
			
			break;}
		}
	
		
	}

    return 0;
}

void initLineTacer() {
    pinMode(LEFT_TRACER_PIN, INPUT);
    pinMode(RIGHT_TRACER_PIN, INPUT);
}


void initUltrasonic(){
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

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
	
}


void goBackward()
{
	digitalWrite(IN1_PIN, LOW);
	digitalWrite(IN2_PIN, HIGH);
	digitalWrite(IN3_PIN, LOW);
	digitalWrite(IN4_PIN, HIGH);
	
}


void goLeft()
{
	digitalWrite(IN1_PIN, LOW);
	digitalWrite(IN2_PIN, HIGH);
	digitalWrite(IN3_PIN, HIGH);
	digitalWrite(IN4_PIN, LOW);
	
}

void goRight()
{
	digitalWrite(IN1_PIN, HIGH);
	digitalWrite(IN2_PIN, LOW);
	digitalWrite(IN3_PIN, LOW);
	digitalWrite(IN4_PIN, HIGH);
	
}

void stopDCMotor()
{
	digitalWrite(IN1_PIN, LOW);
	digitalWrite(IN2_PIN, LOW);
	digitalWrite(IN3_PIN, LOW);
	digitalWrite(IN4_PIN, LOW);
	
}




int getDistance()
{
	int 		start_time=0, end_time=0;
	float 	distance=0;

    digitalWrite(TRIG_PIN, LOW) ;
    delay(500) ;
    digitalWrite(TRIG_PIN, HIGH) ;
    delayMicroseconds(10) ;
    digitalWrite(TRIG_PIN, LOW) ;te
    
    while (digitalRead(ECHO_PIN) == 0) ;
    start_time = micros() ;
    
    while (digitalRead(ECHO_PIN) == 1) ;
    end_time = micros() ;
    
    distance = (end_time - start_time) / 29. / 2. ;
	
	return (int)distance;
}



void lineTracerDetect(){
	
 leftTracer = digitalRead(LEFT_TRACER_PIN);
 rightTracer = digitalRead(RIGHT_TRACER_PIN);
	
	
	if (leftTracer == 0 && rightTracer == 1) {
            printf("Right\n");
			goRight();
			delay(500);


        }
        else if (rightTracer == 0 && leftTracer == 1) {
            printf("Left\n");
			goLeft();
			delay(500);


        }
        else if (rightTracer == 0 && leftTracer == 0) {
            printf("Stop\n");
			stopDCMotor();
			delay(1000);
			test1 = true;
			

        }
        else if (rightTracer == 1 && leftTracer == 1) {
            printf("Forward\n");
			goForward();
			delay(500);

        }
	
	}

//gcc 10-line_tracer_B.c -o lineb -lwiringPi
// ./lineb
