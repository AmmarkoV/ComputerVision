#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Codecs/codecs.h"
 
int writeClassificationOutput(const char * filename,int result)
{
  FILE * fp = fopen(filename,"w");
  if (fp!=0)
    {
      fprintf(fp,"%u\n",result);
      fclose(fp);
    }
}


int processImage(struct Image * image,const char * filename)
{
  if (image!=0)
  {
   if (image->pixels!=0)
   {
    unsigned int pixelChannelIndex = 0;
    for (int y=0; y<image->height; y++)
    {
     for (int x=0; x<image->width; x++)
      {
         char r = image->pixels[pixelChannelIndex + 0];
         char g = image->pixels[pixelChannelIndex + 1];
         char b = image->pixels[pixelChannelIndex + 2];
         
         //Simple filter to make image monochrome 
         int averageColor = (r + g + b)/3; 
         
         image->pixels[pixelChannelIndex + 0] = (char) averageColor; //Write back our new R value
         image->pixels[pixelChannelIndex + 1] = (char) averageColor; //Write back our new G value
         image->pixels[pixelChannelIndex + 2] = (char) averageColor; //Write back our new B value 
         pixelChannelIndex += 3; // we move 3 bytes on each pixel
      }
    }
   return 1; // Let's always return 1 if buffer exists..
   }
  }
 return 0;
}








int main(int argc,const char **argv)
{
  for (int i=1; i<argc; i++)
   {
      char outputFilename[512] = {0};
      const char * filename = argv[i]; //<- our filename given as a parameter to this program

      struct Image * image = readImage(filename,NO_CODEC,0);

      if (image!=0)
        {
          fprintf(stderr,"Just loaded %s \n",filename);  
          fprintf(stderr," It looks like it is %ux%u:%u dimensions \n",image->width,image->height,image->channels);  
          
          fprintf(stderr,"Processing image..\n");  
          int result = processImage(image,filename);

          snprintf(outputFilename,512,"%s-processed.pnm",filename);
          fprintf(stderr,"Writing processed image to %s ..\n",outputFilename);  
          writeImageFile(image,PPM_CODEC,outputFilename);

          snprintf(outputFilename,512,"%s.txt",filename);
          fprintf(stderr,"Writing classification output to %s ..\n",outputFilename);  
          writeClassificationOutput(outputFilename,result);           


          destroyImage(image);
        } 
   }


}
