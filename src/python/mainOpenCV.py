import sys
import os
import cv2

def checkIfFileExists(filename):
    return os.path.isfile(filename) 

def readImage(filename):
    return cv2.imread(filename,cv2.IMREAD_COLOR)

def writeImage(img,filename):
    cv2.imwrite(filename, img) 

def writeClassification(filename,result):
    with open(filename, 'w') as f:
     f.write(str(result)+"\n")

def processImage(img):
    height = img.shape[0]
    width  = img.shape[1]
    
    # loop over the image, pixel by pixel
    for y in range(0, height):
        for x in range(0, width):
            r = img[y,x][0]
            g = img[y,x][1]
            b = img[y,x][2]

            averageValue = ( r + g + b ) / 3
            if (averageValue>255):
                averageValue=255

            img[y,x][0]=averageValue
            img[y,x][1]=averageValue
            img[y,x][2]=averageValue

    # return the thresholded image
    result = 1
    return img,result


if (len(sys.argv)>1):
   for i in range(1, len(sys.argv)):
       filename = sys.argv[i] 
       if (checkIfFileExists(filename)):
         print('Reading image ',filename)
         img = readImage(filename)
         print('Image Dimensions :', img.shape)  

         print('Processing image ',filename)
         processed_image,result = processImage(img)

         print('Writing processed image ',filename)
         writeImage(processed_image,filename+"_processed.jpg")

         print('Writing classification for ',filename)
         writeClassification(filename+".txt",result)

       else:
         print("Could not find : ",filename)
         print("Current directory was : ",os.getcwd())
