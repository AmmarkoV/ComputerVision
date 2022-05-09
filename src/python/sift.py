
# Important NOTE:  Use opencv <= 3.4.2.16 as
# SIFT is no longer available in
# opencv > 3.4.2.16

#python3 -m venv sift_env
#source sift_env/bin/activate
#pip install opencv-contrib-python 

import cv2
import sys


if (len(sys.argv)>1):
       #print('Argument List:', str(sys.argv))
       for i in range(1, len(sys.argv)):
           inputImage=sys.argv[i] 
           
           print("Dumping ",inputImage,"\n")
           # Loading the image
           img = cv2.imread(inputImage)
  
           # Converting image to grayscale
           gray= cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
  
           # Applying SIFT detector
           sift = cv2.SIFT_create()
           #sift = cv2.xfeatures2d.SIFT_create() 
           kp = sift.detect(gray, None)
           kp,des = sift.detectAndCompute(gray, None)
           
           print("Descriptor Dimensions are : ")
           descriptorElements  = len(des[0])
           numberOfDescriptors = len(des)
           print(" ",numberOfDescriptors,"x",descriptorElements)


           f = open(inputImage+"-descriptors.csv", "w")
           f.write("d0")
           for i in range(1,descriptorElements): 
              f.write(",d%u"%i)
           f.write("\n")
           #--------------------------------------------------
           for d in range(0,numberOfDescriptors):
             f.write(str(des[d][0])) 
             for i in range(1,descriptorElements):
               #---------------------------------- 
               f.write(",")
               f.write(str(des[d][i]))
             f.write("\n") 
           f.close()
           #--------------------------------------------------


  
           # Marking the keypoint on the image using circles
           img=cv2.drawKeypoints(gray,
                                 kp,
                                 img,
                                 flags=cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS
                                ) 
           cv2.imwrite(inputImage+'-with-keypoints.jpg', img)
           #--------------------------------------------------





           f = open(inputImage+"-sift.csv", "w")
           f.write("X,Y,Size,Angle,Response,Octave,ClassID\n")
           keypointNumber = 0
           for keypoint in kp: 
               #print("Dumping Keypoint ",keypointNumber) 
               #----------------------------------
               f.write(str(keypoint.pt[0]))
               f.write(",")
               f.write(str(keypoint.pt[1]))
               f.write(",")
               f.write(str(keypoint.size))
               f.write(",")
               f.write(str(keypoint.angle))
               f.write(",")
               f.write(str(keypoint.response))
               f.write(",")
               f.write(str(keypoint.octave))
               f.write(",")
               f.write(str(keypoint.class_id))
               f.write("\n")
               #----------------------------------
               keypointNumber=keypointNumber+1
           f.close()
           #--------------------------------------------------


