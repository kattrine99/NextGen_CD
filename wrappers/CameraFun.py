from turtle import right
import cv2
import numpy as np
import time




def greeting():
    print("CameraFun is avaliable.")


## Image Filters ##

def steering_wheel(data):
    ratio = np.average(data[0:320, 430:470]) / max(np.average(data[320:640, 430:470]), 1)

    if ratio > 4:
        return "right"
    elif ratio < 0.25:
        return "left"

    return "forward"
                    

def preprocessing(frame):
    hsv_img = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    # cv2.imshow("hsv without range", hsv_img)
    hsv_img = cv2.inRange(hsv_img, (20, 30, 120), (67, 180, 227))
    # r = cv2.selectROI(hsv_img)
    # x, y, h, w = 0, 600, 100, 800
    # mask = cv2.inRange()
    # crop = edge_img[y:y + h, x:x + w]
    #kernel = np.ones((7,7),np.uint8)
    #hsv_img = cv2.erode(hsv_img,kernel,iterations = 1)
    
    return hsv_img

## Video Processing ##

def videoFilters(name):
    capture = cv2.VideoCapture(name)

    while True:
        ret, frame = capture.read()

        cv2.imshow('origin', frame)
        cv2.imshow('Honda',preprocessing(frame))
        print(steering_wheel(preprocessing(frame)))
        time.sleep(0.10)

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

def light(frame):
    gamma = 0.75
    lookUpTable = np.empty((1,256), np.uint8)
    for i in range(256):
        lookUpTable[0,i] = np.clip(pow(i / 255.0, gamma) * 255.0, 0, 255)
    output = cv2.LUT(frame, lookUpTable)
    return output

