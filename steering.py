import statistics


def pixel_detect(img):
    indexes = []
    for index, value in enumerate(img):
            if value == 255:
                indexes.append(value)
    me = statistics.mean(indexes)
    right_indexes = []
    left_indexes = []
    for index, value in enumerate(indexes):
        if value >= me:
            left_indexes.append(value)
        else:
            right_indexes.append(value)
    return left_indexes, right_indexes


def line_fitter(pixels, height, img_thr):
    max_pixel = [0, 0]
    for value in pixels:
        frame = img_thr[(value-25):(value+25), (height-25):(height+25)]
        if frame.average > max_pixel[1]:
            max_pixel[1] = frame.average
            max_pixel[0] = value
    return max_pixel[0]


def find_center(left, right, variance_ok):
    center = statistics.mean([left, right])
    print("variance is: " + str(statistics.variance(left, right)))
    if statistics.variance(left, right) < variance_ok:
        lines_status = 'single'
    else:
        lines_status = 'double'
    return center, lines_status  



def right_check(low_center, high_center, steering_threshold):
    if low_center < high_center - steering_threshold:
        return "Right"
    else:
        return "Forward"
    
def left_check(low_center, high_center, steering_threshold):
    if low_center > high_center + steering_threshold:
        return "Left"
    else: 
        return "Forward"

"""
Dear Sarvar

This function consist of several parameters

img_canny - insert canny edged image
img_thr - insert hsv thresholded image

high, low - they can have values of 0-480
at which heights you want to check lines
low is alwaty higher than high

variance_ok - parameter to define acceptable variance to differentiate between 2 lines and single one
function will make prediction and print variances it found on picture, calibrate this value pls to obtain correct results


steering_threshold - number of pixel dead zone for steering mechanism
more threshold = less sensitive steering, pls no more than 100 not less than 20



"""

def get_direction(img_canny, img_thr, variance_ok, steering_threshold, high, low):
    roi_high = img_canny[high, 0:640]
    roi_low = img_canny[low, 0:640]
       
    left_indexes_high, right_indexes_high = pixel_detect(roi_high)

    left_indexes_low, right_indexes_low = pixel_detect(roi_low)
    
    high_center, high_status = find_center(line_fitter(left_indexes_high, img_thr, high), line_fitter(right_indexes_high, img_thr, high), variance_ok)
    
    low_center, low_status = find_center(line_fitter(left_indexes_low, img_thr, low), line_fitter(right_indexes_low, img_thr, low), variance_ok)
   
    if low_status != high_status:
        return "skip"
    
    if high_center > low_center:
        direction = right_check(low_center, high_center, steering_threshold)
    elif high_center < low_center:
        direction = left_check(low_center, high_center, steering_threshold)
    else: 
        direction = "Forward"
    return direction
    
    
        
