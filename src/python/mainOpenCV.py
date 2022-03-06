import sys
import os
import cv2
  

def checkIfFileExists(filename):
    return os.path.isfile(filename) 

def readImage(filename):
    return cv2.imread(filename)


def processImage(image):
    print(image)
    height = image.shape[0]
    width  = image.shape[1]
    
    # loop over the image, pixel by pixel
    for y in range(0, height):
        for x in range(0, width):
            r = image[y,x][0]
            g = image[y,x][1]
            b = image[y,x][2]

            averageValue = ( r + g + b ) / 3
            image[y,x][0]=averageValue
            image[y,x][1]=averageValue
            image[y,x][2]=averageValue

    # return the thresholded image
    return image


if (len(sys.argv)>1):
   for i in range(0, len(sys.argv)):
       filename = sys.argv[i] 
       if (checkIfFileExists(filename)):
         print('Reading image ',filename)
         image = readImage(filename)
         print('Image Dimensions :', image.shape) 
         print(image)

         print('Processing image ',filename)
         processed_image = processImage(image)
       else:
         print("Could not find : ",filename)
         print("Current directory was : ",os.getcwd())
