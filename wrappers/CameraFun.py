import cv2
import numpy as np

def toBinaryImage(image):
	lower_white = np.array([0,0,150])
	upper_white = np.array([179,255,255])

	# convert image to HSV
	hsv = cv2.cvtColor(image,cv2.COLOR_BGR2HSV)
	mask = cv2.inRange(hsv, lower_white, upper_white)
	return mask

def greeting():
	print("CameraFun is avaliable.")

def videoToBinary(capture):
	while True:
	 # ret : frame capture result
	 # frame : Captured frame
	 ret, frame = capture.read()
	 test = toBinaryImage(frame)
	 cv2.imshow('frame', test)
	 #exit 
	 if cv2.waitKey(1) > 0:
	 	break

def playBinaryVideo(name):
	capture = cv2.VideoCapture(name)
	videoToBinary(capture)
	capture.release()

def streamVideo():
	capture = cv2.VideoCapture(0)
	capture.set(3,320) # horizontal pixels
	capture.set(4,240) # vertical pixels

	while True:
		# ret: frame captureresult
		# frame: captured frame
		ret,frame = capture.read()

		if(ret):
			#if capture result was successfull
			gray = cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)

			cv2.imshow('frame',gray)
			if cv2.waitKey(1) > 0:
				break
	capture.release()
