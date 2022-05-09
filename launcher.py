import wrappers.MoveFun as move
import wrappers.UltraSonic as sonic

import cv2
import numpy as np
import time




def test():
    #move.goForward(3)
    #move.goSmoothRight(0.2 , 1, 0.001)
    #move.goSmoothLeft(0.4, 0.0005, 1)
    time.sleep(0.5)
    #move.goSmoothRight(0.3 , 1, 0.001)

def preprocess(frame):
    roi = frame[360:frame.shape[0],0:frame.shape[1]]

    hsv = cv2.cvtColor(roi, cv2.COLOR_BGR2HSV)
    lower_white = np.array([0,37,80])
    upper_white = np.array([59,255,255])
    treshold = cv2.inRange(hsv, lower_white, upper_white)

    gray = cv2.cvtColor(roi,cv2.COLOR_BGR2GRAY)
    equ = cv2.equalizeHist(gray)
    gauss = cv2.GaussianBlur(equ,(5,5),0)
    
    edge = cv2.Canny(gauss,50,150)

    kernel = np.ones((7,7),np.uint8)
    edge = cv2.dilate(edge,kernel,iterations = 1)

    return edge,treshold

def average_slope_intercept(lines):
    left_fit=[]
    right_fit=[]
    if lines is not None:
        for line in lines:
            x1,y1,x2,y2=line.reshape(4)
            parameters=np.polyfit((x1,x2),(y1,y2),1)
            slope=parameters[0]
            intercept=parameters[1]
            if slope<0:
                right_fit.append((slope,intercept))
            else:
                left_fit.append((slope,intercept))
 
    left_fitavg=np.average(left_fit, axis=0)
    right_fitavg=np.average(right_fit, axis=0)
    print("left slope",left_fitavg,"rigt slope",right_fitavg)

    return len(left_fit), len(right_fit)

def display_lines(lines,image):
    line_image=np.zeros_like(image)
    if lines is not None:
        for line in lines:
            if len(line)>0:                    
                x1,y1,x2,y2=line.reshape(4)
                cv2.line(line_image,(x1,y1),(x2,y2),[0,255,0],10)
    return line_image

def processVideo():
    capture = cv2.VideoCapture("video/new_map 30 fps light on.avi")
    command = "None"
    prev_command = "None" # previous command

    while True:
        ret, frame = capture.read()
        

        edge,treshold = preprocess(frame)

        merged = cv2.bitwise_and(edge,treshold,mask = None)
    
        lines=cv2.HoughLinesP(merged,1,np.pi/180,30,np.array([]),minLineLength=20,maxLineGap=5)
        num_left_lines,num_right_lines = average_slope_intercept(lines)
        print("# of left: "+str(num_left_lines)+ " # of right: "+ str(num_right_lines))
        frame_with_lines = display_lines(lines,frame[360:frame.shape[0],0:frame.shape[1]])
 
        if(num_left_lines != 0 and num_right_lines != 0):
            if((num_right_lines / num_left_lines) <2 or (num_left_lines / num_right_lines) < 2):
                command = "Forward"
        elif(num_left_lines > num_right_lines):
            command = "Left"
        elif(num_right_lines> num_left_lines):
            command = "Right"
    
        prev_command = command

        if(num_left_lines == 0 and num_right_lines == 0):
            command = prev_command

        

        if(command == "Forward"):
            ## move forward
            print("Forward")
            #move.goForward(0.05)
        elif(command == "Right"):
            ## move right
            print("Right")
            #move.goSmoothRight(0.05)
        elif(command == "Left"):
            ## move Left
            print("Left")
            #move.goSmoothLeft(0.05)

        cv2.imshow('Origin',frame)
        cv2.imshow('Lines',frame_with_lines)
        time.sleep(0.10)
        #exit
        if cv2.waitKey(1) > 0:
            break
    capture.release()

def processVideoOFF():
    capture = cv2.VideoCapture(0)
    command = "None"
    prev_command = "None" # previous command

    while True:
        ret, frame = capture.read()

        edge,treshold = preprocess(frame)

        merged = cv2.bitwise_and(edge,treshold,mask = None)
    
        lines=cv2.HoughLinesP(merged,1,np.pi/180,30,np.array([]),minLineLength=20,maxLineGap=5)
        num_left_lines,num_right_lines = average_slope_intercept(lines)

        #print("# of left: "+str(num_left_lines)+ " # of right: "+ str(num_right_lines))

        #frame_with_lines = display_lines(lines,frame[360:frame.shape[0],0:frame.shape[1]])
 
        if(num_left_lines != 0 and num_right_lines != 0):
            if((num_right_lines / num_left_lines) <2 or (num_left_lines / num_right_lines) < 2):
                command = "Forward"
        elif(num_left_lines > num_right_lines):
            command = "Left"
        elif(num_right_lines> num_left_lines):
            command = "Right"
    
        prev_command = command

        if(num_left_lines == 0 and num_right_lines == 0):
            command = prev_command

        if(command == "Forward"):
            ## move forward
            print("Forward")
            move.goForward(0.2)
        elif(command == "Right"):
            ## move right
            print("Right")
            move.goSmoothRight(0.2 , 1, 0.001)
        elif(command == "Left"):
            ## move Left
            print("Left")
            move.goSmoothLeft(0.2, 0.0005, 1)

        #cv2.imshow('Origin',frame)
        #cv2.imshow('Lines',frame_with_lines)
        time.sleep(0.10)
        #exit
        if cv2.waitKey(1) > 0:
            break
    capture.release()    
     

## Main ##

#test()

"""while True:
      command="none"
      command= sonic.checkDistance() 
      if(command=="forward"):
         move.goForward()
      elif(command =="stop"):
          move.stopDCMotor()
       
        """

#processVideo()

processVideoOFF()

