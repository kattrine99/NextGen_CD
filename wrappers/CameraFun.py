import cv2
import numpy as np

from picamera.array import PiRGBArray
from picamera import PiCamera
import time

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

def StreamAndRecordVideo():
	capture = cv2.VideoCapture(0)

	#Define the codec and create VideoWriter object
	fourcc = cv2.VideoWriter_fourcc('M','J','P','G')
	out = cv2.VideoWriter('output.avi', fourcc, 20.0,(640,480))

	while capture.isOpened():
		ret,frame = capture.read()
		if not ret:
			print("Can't receive frame (stream end?). Exiting...")
			break
		#frame = cv2.flip(frame,0)

		#Write the flipped frame
		out.write(frame)

		cv2.imshow('frame', frame)
		if cv2.waitKey(1) == ord('q'):
			break

	# Release everything if job is finished
	capture.release()
	out.release()
	cv2.destroyAllWindows()

def playVideoFromFile(name):
	capture = cv2.VideoCapture(name)
	while True:
		# ret : frame capture result
		# frame : Captured frame
		ret, frame = capture.read()
		# convert image to Grayscale
		#gray = cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)
		cv2.imshow('frame', frame)
		if cv2.waitKey(1) > 0:
			break
	capture.release()

def rawVideoCapture():
	# initialize the camera and grab a reference to the raw camera capture
	camera = PiCamera()
	camera.resolution = (640,480)
	camera.framerate = 32
	rawCapture = PiRGBArray(camera, size=(640,480))
	# allow the camera to warmup
	time.sleep(0.1)

	# capture frames from the camera
	for frame in camera.capture_continuous(rawCapture, format = "bgr", use_video_port = True):
		# grab the raw NumPy array representing the image, then initialize the timestamp
		# and occupied/unoccupied text
		image = frame.array
		# show the frame
		cv2.imshow("Frame", image)
		key = cv2.waitKey(1) & 0xFF
		# clear the stream in preparation for the next frame
		rawCapture.truncate(0)
		# if the `q` key was pressed, break from the loop
		if key == ord ("q"):
			break
