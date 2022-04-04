import cv2
import numpy as np

def greeting():
	print("CameraFun is avaliable.")


## Image Filters ##

def toBinaryImage(image):
	lower_white = np.array([0,0,150])
	upper_white = np.array([179,255,255])
	mask = cv2.inRange(toHSVImage(image), lower_white, upper_white)
	return mask

def toHSVImage(image):
	#temp = cv2.cvtColor(image, cv2.COLOR_GRAY2BGR)
	hsv = cv2.cvtColor(image,cv2.COLOR_BGR2HSV)
	return hsv

def toGaussImage(image):
	blur_img = cv2.GaussianBlur(image,(5,5),0)
	return blur_img

def toGrayImage(image):
	gray = cv2.cvtColor(image,cv2.COLOR_BGR2GRAY)
	return gray

def toEdgeImage(image):
	edge = cv2.Canny(image,50,150)
	return edge

def toBlendimage(image1,image2,alpha = 0.5):
	beta = (1.0 - alpha)
	result = cv2.addWeighted(image1,alpha,image2,beta,0.0)
	return result

def toErodeImage(image):
	kernel = np.ones((7,7),np.uint8)
	erosion = cv2.erode(image,kernel,iterations = 1)
	return erosion


## Video Processing ##

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

def videoFilters(name):
	# Each frame proceed through these procedures:
	# Read image -> GrayScale -> Gaussian Blur -> Canny edge -> HSV to Binary
	capture = cv2.VideoCapture(name)
	while True:
		ret, frame = capture.read()

		roi = frame[240:480,0:640]
		# GrayScale
		gray = toGrayImage(roi)

		# Gaussian Blur
		gauss = toGaussImage(gray)

		#Canny edge 
		edge = toEdgeImage(gauss)

		#HSV to Binary
		binary = toBinaryImage(roi)

		cv2.imshow('binary', binary)
		cv2.imshow('edge', edge)
		cv2.imshow('gauss', gauss)

		#exit 
		if cv2.waitKey(1) > 0:
			break
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