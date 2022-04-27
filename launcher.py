import wrappers.MoveFun as move
import wrappers.CameraFun as camera

import cv2


def final():
    capture = cv2.VideoCapture(0)
    while capture.isOpened():
        ret,frame = capture.read()
        if not ret:
            print("Can't receive frame (stream end?). Exiting...")
            break

        command = camera.preprocessing(frame)
        print(camera.steering_wheel(camera.preprocessing(frame)))

        if( command == "forward"):
            move.goForward(0.05)
        elif (command == "right"):
            move.goSmoothRight(0.05)
        elif( command == "left"):
            move.goSmoothLeft(0.05)


        
        if cv2.waitKey(1) == ord('q'):
            move.stopDCMotor()
            break

    # Release everything if job is finished
    move.stopDCMotor()
    capture.release()
    cv2.destroyAllWindows()






## Write your code below ## 

final()

#camera.videoFilters("video/new_map 30 fps light on.avi")
#camera.StreamAndRecordVideo()

