import wrappers.MoveFun as move
import wrappers.UltraSonic as sonic

import cv2
import numpy as np
import time

def steering_wheel(data, threshold):
    left = int(np.average(data[370:460, 130:200])) 
    right = int(np.average(data[370:460, 440:510]))
    
    if (left > threshold and right < threshold):
        command = "Right"
    elif (left < threshold and right > threshold):
        command = "Left"
    elif left < threshold and right < threshold:
        command = "Forward"
    else:
        command = "Forward"
    return command, "left:" + str(left) + "  right:" + str(right)
        

def moments(data, threshold):
    top = data[350:380, 0:640]
    bot = data[430:460, 0:640]
    left = int(np.average(top))
    right = int(np.average(bot))
    
    
        
    
    command = "Forward"
    Mtop = cv2.moments(top)
    Mbot = cv2.moments(bot)
    
    ctop = int(Mtop["m10"] / max(Mtop["m00"], 1))
    cbot = int(Mbot["m10"] / max(Mbot["m00"], 1))
    
    
    
    moment = ctop-cbot
    neg_thr = 0-threshold
    if (moment) > threshold:
        command = "Right"
        
    elif (moment) < (neg_thr):
        command = "Left"
        
    if (left< 1) or (right <1):
        command = "Forward"
        
    return command, "top:" + str(ctop) + "   bot:" + str(cbot), ctop, cbot




def preprocess(roi):
    hsv = cv2.cvtColor(roi, cv2.COLOR_BGR2HSV)
    lower_white = np.array([25,37,80])
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
    #print("left slope",left_fitavg,"rigt slope",right_fitavg)

    return len(left_fit), len(right_fit)

def display_lines(lines,image):
    line_image=np.zeros_like(image)
    if lines is not None:
        for line in lines:
            if len(line)>0:                    
                x1,y1,x2,y2=line.reshape(4)
                cv2.line(line_image,(x1,y1),(x2,y2),[0,255,0],10)
    return line_image


def processVideoOFF():
    capture = cv2.VideoCapture(0)
    
    #Define the codec and create VideoWriter object
    #ourcc = cv2.VideoWriter_fourcc('M','J','P','G')
    #out = cv2.VideoWriter('for_honda.avi', fourcc, 30.0,(640,480))
    
    
    command = "None"
    buffer = "Forward"
    prev_command = "None" # previous command
    frame_number = 0
    font = cv2.FONT_HERSHEY_SIMPLEX
    
    

    while True:
        ret, frame = capture.read()
        #
        move.goForward()
        #cv2.putText(frame,str(steering_wheel(edge)),(10,30), font, 1,(0,0,255),2,cv2.LINE_AA)
        
        
        #out.write(frame)

            
        edge,treshold = preprocess(frame)
        #command, status = steering_wheel(edge, 25)
        command, moment, ctop, cbot = moments(treshold, 35)
        #cv2.putText(frame,str(command) + "/n" + moment,(10,30), font, 1,(0,0,255),2,cv2.LINE_AA)
    
        #frame_with_lines = display_lines(lines,roi)

        
        if(command == "Right"):
            ## move right
            print("Decision: Right")
            move.goRight(0.05)
            
        elif(command == "Left"):
            ## move Left
            print("Decision: Left")
            move.goLeft(0.05)

        frame = cv2.rectangle(frame,(130,370),(200,480),(255,255,255),-1)
        frame = cv2.rectangle(frame,(440,370),(510,480),(255,255,255),-1)
        cv2.imshow('Origin',frame)
        cv2.imshow('edge',treshold)
        #cv2.imshow('Lines',frame_with_lines)
        #time.sleep(0.10)
        #exit
        if cv2.waitKey(1) > 0:
            break
    capture.release()    
     

## Main ##


def test():
    while True:
      command="none"
      command= sonic.checkDistance() 
      if(command=="forward"):
          #move.goForward()
          print("Forward")
      elif(command =="stop"):
          #move.stopDCMotor()
          print("Stop")
       
        
#test()
#processVideo()

processVideoOFF()

