#include <stdio.h>
#include <wiringPi.h>


#define LEFT_TRACER_PIN 10
#define RIGHT_TRACER_PIN 11


void initLineTacer();

int main(void){
    
    if(wiringPiSetup() == -1)
	    return 0;
    
    initLineTacer();
    
    int leftTracer;
    int rightTracer;
  
    while (1) {
		 
	leftTracer = digitalRead(LEFT_TRACER_PIN);
	rightTracer = digitalRead(RIGHT_TRACER_PIN);
   
         if (leftTracer == 0 && rightTracer == 1) {
             printf("Left\n");      
            

         }else if (rightTracer ==0 && leftTracer == 1) {
               printf("Right\n");   
            
                  
         }else if (rightTracer == 0 && leftTracer == 0) {
               printf("Both\n");   
                  
                    
                               
         }else if (rightTracer == 1 && leftTracer == 1) {
              printf("No\n");    
            
         }     
	 }
     return 0;
}

void initLineTacer(){
	pinMode(LEFT_TRACER_PIN, INPUT);
	pinMode(RIGHT_TRACER_PIN, INPUT);		
}

//gcc 8-line_tracer_ex.c -o linex -lwiringPi
// ./linex

