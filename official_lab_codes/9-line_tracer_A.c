#include <stdio.h>
#include <wiringPi.h>


#define LEFT_TRACER_PIN 10
#define RIGHT_TRACER_PIN 11


#define IN1_PIN		1
#define IN2_PIN		4
#define IN3_PIN		5
#define IN4_PIN		6


void initLineTacer();
void initDCMotor();
void goForward();
void goBackward();
void goLeft();
void goRight();
void stopDCMotor();



int main(void) {

    if (wiringPiSetup() == -1)
        return 0;

    initLineTacer();
	initDCMotor();

    int leftTracer;
    int rightTracer;

    while (1) {

        leftTracer = digitalRead(LEFT_TRACER_PIN);
        rightTracer = digitalRead(RIGHT_TRACER_PIN);

        if (leftTracer == 0 && rightTracer == 1) {
            printf("Left\n");
			goRight();
			delay(500);


        }
        else if (rightTracer == 0 && leftTracer == 1) {
            printf("Right\n");
			goLeft();
			delay(500);


        }
        else if (rightTracer == 0 && leftTracer == 0) {
            printf("Both\n");
			stopDCMotor();
			delay(1000);
			break;

        }
        else if (rightTracer == 1 && leftTracer == 1) {
            printf("No\n");
			goForward();
			delay(500);

        }
    }
    return 0;
}

void initLineTacer() {
    pinMode(LEFT_TRACER_PIN, INPUT);
    pinMode(RIGHT_TRACER_PIN, INPUT);
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



//gcc 9-line_tracer_A.c -o linea -lwiringPi
// ./linea

