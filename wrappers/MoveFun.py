import RPi.GPIO as GPIO
from gpiozero import Motor
import time
from time import sleep

GPIO.setmode(GPIO.BCM)
left = Motor(18, 23) # left pair of Motors
right = Motor(24, 25) # right pair of Motors



def help():
    print("#### HELP ####\n")
    print("1. help() - show all functions and their arguments.\n")
    print("2. goForward(duration: int, speed: float) - moves car forward. Note! speed is in range 0 and 1.\n")
    print("3. goBackward(duration: int, speed: float) - moves car backward. Note! speed is in range 0 and 1.\n")
    print("4. goLeft(duration: int) - turns car left.\n")
    print("5. goRight(duration: int) - turns car right.\n")
    print("6. goSmoothLeft(duration: int,leftCoef: float , rightCoef: float) - turns car left smoothly. Note! rightCoef/leftCoef is in range 0 and 1\n")
    print("7. goSmoothRight(duration: int,leftCoef: float , rightCoef: float) - turns car right smoothly. Note! rightCoef/leftCoef is in range 0 and 1\n")
    print("8. goSmoothBackLeft(duration: int,leftCoef: float , rightCoef: float) - turns car backward left smoothly. Note! rightCoef/leftCoef is in range 0 and 1\n")
    print("9. goSmoothBackRight(duration: int,leftCoef: float , rightCoef: float) - turns car backward right smoothly. Note! rightCoef/leftCoef is in range 0 and 1\n")
    print("10. stopDCMotor() - stop car.\n")

def goForward(duration, speed = 0.5):
    
    print("Moving forward for "+ str(duration)+" s " +"with speed = "+ str(speed))
    left.forward(speed)
    right.forward(speed)
    time.sleep(duration)
    stopDCMotor()

def goBackward(duration, speed = 0.5):
    print("Moving backward for "+ str(duration)+" s " +"with speed = "+str(speed))
    left.backward(speed)
    right.backward(speed)
    time.sleep(duration)
    stopDCMotor()

def goLeft(duration):
    print("Moving left for "+ str(duration)+" s")
    left.backward()
    right.forward()
    time.sleep(duration)
    stopDCMotor()

def goRight(duration):
    print("Moving right for "+ str(duration)+" s")
    left.forward()
    right.backward()
    time.sleep(duration)
    stopDCMotor()

def goSmoothLeft(duration, leftCoef = 0.1 , rightCoef = 0.5):
    print("Moving smooth left for "+ str(duration)+" s, "+"leftCoef = "+ str(leftCoef) + ", rightCoef = " + str(rightCoef))
    left.forward(leftCoef)
    right.forward(rightCoef)
    time.sleep(duration)
    stopDCMotor()

def goSmoothRight(duration, leftCoef = 0.5 , rightCoef = 0.1):
    print("Moving smooth right for "+ str(duration)+" s, "+"leftCoef = "+ str(leftCoef) + ", rightCoef = " + str(rightCoef))
    left.forward(leftCoef)
    right.forward(rightCoef)
    time.sleep(duration)
    stopDCMotor()

def goSmoothBackLeft(duration, leftCoef = 0.1 , rightCoef = 0.5):
    print("Moving smooth back left for "+ str(duration)+" s, "+"leftCoef = "+ str(leftCoef) + ", rightCoef = " + str(rightCoef))
    left.backward(leftCoef)
    right.backward(rightCoef)
    time.sleep(duration)
    stopDCMotor()

def goSmoothBackRight(duration, leftCoef = 0.5 , rightCoef = 0.1):
    print("Moving smooth back right for "+ str(duration)+" s, "+"leftCoef = "+ str(leftCoef) + ", rightCoef = " + str(rightCoef))
    left.backward(leftCoef)
    right.backward(rightCoef)
    time.sleep(duration)
    stopDCMotor()

def stopDCMotor():
    left.stop()
    right.stop()

