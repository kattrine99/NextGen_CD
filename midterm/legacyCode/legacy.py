import cv2
import numpy as np
import time

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

def computeWhiteArea(image,tag):
    size = np.size(image)
    white_area = cv2.countNonZero(image)
    black_area = size - white_area
    white_percentage = round((white_area * 100 / size),2)
    print("White area persentage of "+str(tag) +" "+str(white_percentage) + "%")
    return white_percentage

def drawRectangle(image):
    #Convert Frame->HSV->binary image
    hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
    lower_white = np.array([20,60,140])
    upper_white = np.array([179,255,255])
    mask = cv2.inRange(hsv, lower_white, upper_white)

    # Select a Region of Interest for frame (2 lines)
    # ROI of left and right trace
    roi_left= mask[350:390,100:130] 
    roi_right = mask[350:390,490:520]

    # Compute White/Black area of Left/Right RoI
    left_white_result = computeWhiteArea(roi_left,"Left RoI")
    right_white_result =computeWhiteArea(roi_right,"Right RoI")

    # If percentage is equal or above 50% we can assume that RoI contains a trace or a part of it
    if(left_white_result >= 25.0):
        #Draw a rectangle
        print("Drawing rectangle (Left)")
        #Take original frame and using coordinates of RoI draw a rectangle
        image = cv2.rectangle(image,(100,350),(130,390),(0,255,0),3)
    else: 
        #No need in rectangle
        print("No trace")
        
    if(right_white_result >= 25.0):
        #Draw a rectangle
        print("Drawing rectangle (Right)")
        #Take original frame and using coordinates of RoI draw a rectangle
        image = cv2.rectangle(image,(490,350),(520,390),(0,255,0),3)
    else: 
        #No need in rectangle
        print("No trace")
    
    # Submit result
    return image

def toBlendimage(image1,image2,alpha = 0.5):
    beta = (1.0 - alpha)
    result = cv2.addWeighted(image1,alpha,image2,beta,0.0)
    return result

def toErodeImage(image):
    kernel = np.ones((7,7),np.uint8)
    erosion = cv2.erode(image,kernel,iterations = 1)
    return erosion

def getContour(source,result):
    #Creating a contour 
    _,contours,hierarchy = cv2.findContours(source,1,cv2.CHAIN_APPROX_NONE)
    cv2.drawContours(result,contours,-1,[0,255,0],1)

def region_of_interest(img,vertices):
    mask = np.zeros_like(img)
    #channel_count = image.shape[2]
    #match_mask_color = (255,) * channel_count
    match_mask_color = 255
    cv2.fillPoly(mask,vertices,match_mask_color)
    masked_image = cv2.bitwise_and(img,mask)
    return masked_image

def draw_the_lines(img, lines):
    img = np.copy(img)
    blank_image = np.zeros((img.shape[0],img.shape[1], 3), dtype = np.uint8)
    
    if lines is not None:
        for line in lines:
            for x1,y1,x2,y2 in line:
                cv2.line(blank_image,(x1,y1),(x2,y2),(0,255,0),thickness = 3)
    
    img = cv2.addWeighted(img, 0.8, blank_image, 1, 0.0)
    return img

def processImage(image):

    height = image.shape[0]
    width = image.shape[1]

    region_of_interest_vertices = [
    (0,height),
    (225,240),
    (420,240),
    (width,height)
    ]

    gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    canny_image = cv2.Canny(gray_image,20, 130)
   
    cropped_image = region_of_interest(canny_image,
    np.array([region_of_interest_vertices], np.int32))

    lines = cv2.HoughLinesP(cropped_image, rho = 6, theta = np.pi/600, threshold = 160, 
    lines = np.array([]),
    minLineLength = 40,
    maxLineGap = 25)

    image_with_lines = draw_the_lines(image, lines)

    return image_with_lines