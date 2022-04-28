import cv2
import numpy as np
import time

def nothing(x):
    pass

cv2.namedWindow("Trackbars")

cv2.createTrackbar("L-H","Trackbars",0,255,nothing)
cv2.createTrackbar("L-S","Trackbars",0,255,nothing)
cv2.createTrackbar("L-V","Trackbars",0,255,nothing)
cv2.createTrackbar("U-H","Trackbars",0,255,nothing)
cv2.createTrackbar("U-S","Trackbars",0,255,nothing)
cv2.createTrackbar("U-V","Trackbars",0,255,nothing)

capture = cv2.VideoCapture("video/new_map 30 fps light on.avi")

while True:
        ret, frame = capture.read()


        hsv = cv2.cvtColor(frame,cv2.COLOR_BGR2HSV)

        l_h = cv2.getTrackbarPos("L-H","Trackbars")
        l_s = cv2.getTrackbarPos("L-S","Trackbars")
        l_v = cv2.getTrackbarPos("L-V","Trackbars")
        u_h = cv2.getTrackbarPos("U-H","Trackbars")
        u_s = cv2.getTrackbarPos("U-S","Trackbars")
        u_v = cv2.getTrackbarPos("U-V","Trackbars")

       

        # Apply masking
        lower_white = np.array([l_h,l_s,l_v])
        upper_white = np.array([u_h,u_s,u_v])
        mask = cv2.inRange(hsv, lower_white, upper_white)

        cv2.imshow('Original', frame)
        cv2.imshow('Binary', mask)
        
        time.sleep(0.05)

        #exit 
        if cv2.waitKey(1) > 0:
            break

capture.release()
