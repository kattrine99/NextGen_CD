import cv2

capture = cv2.VideoCapture("my_movie.avi")

while True:
	f# ret : frame capture result
	# frame : Captured frame
	ret, frame = capture.read()

	# convert image to Grayscale
	gray = cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)
	cv2.imshow('frame', gray)
	if cv2.waitKey(1) > 0:
		break


capture.release()
cv2.destroyAllWindows()