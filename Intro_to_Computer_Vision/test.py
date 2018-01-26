import cv2 

# img = cv2.imread("./img/exit-ramp.jpg")
cap = cv2.VideoCapture(0)

if (~cap.isOpened()):
    print ("ssss")
else:
    print ("olala")
