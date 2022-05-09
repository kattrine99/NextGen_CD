import RPi.GPIO as GPIO
from gpiozero import Motor
from time import sleep
import time

TRIG=20
ECHO=21

def getDistance():
  
  GPIO.setup(TRIG, GPIO.OUT)
  GPIO.setup(ECHO, GPIO.IN)
  GPIO.output(TRIG, False)
 
  time.sleep(0.001)
  GPIO.output(TRIG, True)
  time.sleep(0.000001)
  GPIO.output(TRIG, False)
  start=time.time()
  
  while GPIO.input(ECHO)==0:
	   start=time.time()
	   
  while GPIO.input(ECHO)==1:
       stop=time.time()
  pulse_duration=stop-start
  
  distance=pulse_duration*17150
  distance=round(distance, 2)
  distance = distance / 2
  print ("Distance : %.1f" % distance)
  
  return distance

def checkDistance():
	dist = getDistance()
	command = "none"
	if(dist > 20.0):
		command = "forward"
	elif(dist < 20.0):
		command = "stop"
	return command
		
