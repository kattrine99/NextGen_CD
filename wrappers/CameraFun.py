import cv2
import numpy as np
import time

import matplotlib.pyplot as plt

def greeting():
    print("CameraFun is avaliable.")


## Image Filters ##

def steering_wheel(data):
    ratio = np.average(data[0:320, 430:480]) / max(np.average(data[320:640, 430:480]), 1)
    if ratio > 2:
        return "right"
    elif ratio < 0.5:
        return "left"
    return "forward"
                    

def preprocessing(frame):
    hsv_img = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    # cv2.imshow("hsv without range", hsv_img)
    hsv_img = cv2.inRange(hsv_img, (0, 30, 120), (67, 255, 227))
    # r = cv2.selectROI(hsv_img)
    # x, y, h, w = 0, 600, 100, 800
    # mask = cv2.inRange()
    # crop = edge_img[y:y + h, x:x + w]  
    
    return hsv_img

## Video Processing ##

def videoFilters(name):
    capture = cv2.VideoCapture(name)

    while True:
        ret, frame = capture.read()

        cv2.imshow('origin', frame)
        cv2.imshow('Honda',preprocessing(frame))
        print(steering_wheel(preprocessing(frame)))
        time.sleep(0.05)

        #exit 
        if cv2.waitKey(1) > 0:
            break
    capture.release()

def StreamAndRecordVideo():
    capture = cv2.VideoCapture(0)

    #Define the codec and create VideoWriter object
    fourcc = cv2.VideoWriter_fourcc('M','J','P','G')
    out = cv2.VideoWriter('output.avi', fourcc, 30.0,(640,480))

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