#include "opencv2/opencv.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace cv;

int writeClassificationOutput(const char * filename,int result)
{
  FILE * fp = fopen(filename,"w");
  if (fp!=0)
    {
      fprintf(fp,"%u\n",result);
      fclose(fp);
      return 1;
    }
  return 0;
}



int processImage(cv::Mat & image,const char * filename,unsigned int width,unsigned int height,unsigned int channels)
{
  if (image.data!=0)
  {
  unsigned int pixelChannelIndex = 0;
  for (int y=0; y<height; y++)
   {
     for (int x=0; x<width; x++)
      {
         char r = image.data[pixelChannelIndex + 0];
         char g = image.data[pixelChannelIndex + 1];
         char b = image.data[pixelChannelIndex + 2];

         //Simple filter to make image monochrome
         int averageColor = (r + g + b)/3;

         image.data[pixelChannelIndex + 0] = (char) averageColor; //Write back our new R value
         image.data[pixelChannelIndex + 1] = (char) averageColor; //Write back our new G value
         image.data[pixelChannelIndex + 2] = (char) averageColor; //Write back our new B value
         pixelChannelIndex += 3; // we move 3 bytes on each pixel
      }
   }
  return 1; // Let's always return 1 if buffer exists..
  }
 return 0;
}



int main(int argc,const char **argv)
{
  for (int i=1; i<argc; i++)
   {
      char outputFilename[512] = {0};
      const char * filename = argv[i]; //<- our filename given as a parameter to this program

      cv::Mat image = cv::imread(filename, CV_LOAD_IMAGE_COLOR);   // Read the file;
      
      if (image.data!=0)
        {
          fprintf(stderr,"Just loaded %s \n",filename);
          fprintf(stderr," It looks like it is %ux%u dimensions \n",image.size().width,image.size().height);

          int result = processImage(image,filename,image.size().width,image.size().height,image.channels());

          snprintf(outputFilename,512,"%s-processed.png",filename);
          cv::imwrite(outputFilename,image);
          
          cv::imshow( "Display window", image );  // Show our image live! 
          waitKey(10); //Wait 10 milliseconds        

          snprintf(outputFilename,512,"%s.txt",filename);
          writeClassificationOutput(outputFilename,result);
        }
   }
 return 0;
}
