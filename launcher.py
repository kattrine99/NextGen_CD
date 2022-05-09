import wrappers.MoveFun as move
import wrappers.CameraFun as camera
import wrappers.UltraSonic as sonic

import cv2
import time


def final():
    capture = cv2.VideoCapture(0)
    
    #Define the codec and create VideoWriter object
    #fourcc = cv2.VideoWriter_fourcc('M','J','P','G')
    #out = cv2.VideoWriter('output.avi', fourcc, 30.0,(640,480))
    
    time.sleep(0.2)
    while capture.isOpened():
        ret,frame = capture.read()
        if not ret:
            print("Can't receive frame (stream end?). Exiting...")
            break
        ##out.write(frame)
        cv2.imshow('test',camera.preprocessing(frame))
        command = camera.steering_wheel(camera.preprocessing(frame))
        #command = " "
        print(command)
        
        
        
        if( command == "forward"):
            move.goForward(0.1)
        elif (command == "right"):
            move.goRight(0.1)
        elif( command == "left"):
            move.goLeft(0.1)

        
        if cv2.waitKey(1) == ord('q'):
            move.stopDCMotor()
            break

    # Release everything if job is finished
    move.stopDCMotor()
    #out.release()
    capture.release()
    cv2.destroyAllWindows()

def test():
    
     move.goForward(3)
     #move.goSmoothRight(0.2 , 1, 0.001)
     move.goSmoothLeft(0.4, 0.0005, 1)
     time.sleep(0.5)
     move.goSmoothRight(0.3 , 1, 0.001)
     
     





## Write your code below ## 

#final()
test()
"""while True:
      command="none"
      command= sonic.checkDistance() 
      if(command=="forward"):
         move.goForward()
      elif(command =="stop"):
          move.stopDCMotor()
       
        """
#camera.videoFilters("video/new_map 30 fps light on.avi")
#camera.StreamAndRecordVideo()

