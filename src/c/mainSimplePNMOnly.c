#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PPMREADBUFLEN 256

unsigned int simplePow(unsigned int base,unsigned int exp)
{
    if (exp==0) return 1;
    unsigned int retres=base;
    unsigned int i=0;
    for (i=0; i<exp-1; i++)
    {
        retres*=base;
    }
    return retres;
}

unsigned char * ReadPNM(unsigned char * buffer ,const char * filename,unsigned int *width,unsigned int *height,unsigned long * timestamp , unsigned int * bytesPerPixel , unsigned int * channels)
{
   * bytesPerPixel = 0;
   * channels = 0;

    //See http://en.wikipedia.org/wiki/Portable_anymap#File_format_description for this simple and useful format
    unsigned char * pixels=buffer;
    FILE *pf=0;
    pf = fopen(filename,"rb");

    if (pf!=0 )
    {
        *width=0; *height=0; *timestamp=0;

        char buf[PPMREADBUFLEN]={0};
        char *t;
        unsigned int w=0, h=0, d=0;
        int r=0 , z=0;

        t = fgets(buf, PPMREADBUFLEN, pf);
        if (t == 0) { fclose(pf); return buffer; }

        if ( strncmp(buf,"P6\n", 3) == 0 ) { *channels=3; } else
        if ( strncmp(buf,"P5\n", 3) == 0 ) { *channels=1; } else
                                           { fprintf(stderr,"Could not understand/Not supported file format\n"); fclose(pf); return buffer; }
        do
        { /* Px formats can have # comments after first line */
           #if PRINT_COMMENTS
             memset(buf,0,PPMREADBUFLEN);
           #endif
           t = fgets(buf, PPMREADBUFLEN, pf);
           if (strstr(buf,"TIMESTAMP")!=0)
              {
                char * timestampPayloadStr = buf + 10;
                *timestamp = atoi(timestampPayloadStr);
              }

           if ( t == 0 ) { fclose(pf); return buffer; }
        } while ( strncmp(buf, "#", 1) == 0 );
        z = sscanf(buf, "%u %u", &w, &h);
        if ( z < 2 ) { fclose(pf); fprintf(stderr,"Incoherent dimensions received %ux%u \n",w,h); return buffer; }
        // The program fails if the first byte of the image is equal to 32. because
        // the fscanf eats the space and the image is read with some bit less
        r = fscanf(pf, "%u\n", &d);
        if (r < 1) { fprintf(stderr,"Could not understand how many bytesPerPixel there are on this image\n"); fclose(pf); return buffer; }
        if (d==255) { *bytesPerPixel=1; }  else
        if (d==65535) { *bytesPerPixel=2; } else
                       { fprintf(stderr,"Incoherent payload received %u bits per pixel \n",d); fclose(pf); return buffer; }


        //This is a super ninja hackish patch that fixes the case where fscanf eats one character more on the stream
        //It could be done better  ( no need to fseek ) but this will have to do for now
        //Scan for border case
           unsigned long startOfBinaryPart = ftell(pf);
           if ( fseek (pf , 0 , SEEK_END)!=0 ) { fprintf(stderr,"Could not find file size to cache client..!\nUnable to serve client\n"); fclose(pf); return 0; }
           unsigned long totalFileSize = ftell (pf); //lSize now holds the size of the file..

           //fprintf(stderr,"totalFileSize-startOfBinaryPart = %u \n",totalFileSize-startOfBinaryPart);
           //fprintf(stderr,"bytesPerPixel*channels*w*h = %u \n",bytesPerPixel*channels*w*h);
           if (totalFileSize-startOfBinaryPart < *bytesPerPixel*(*channels)*w*h )
           {
              fprintf(stderr," Detected Border Case\n\n\n");
              startOfBinaryPart-=1;
           }
           if ( fseek (pf , startOfBinaryPart , SEEK_SET)!=0 ) { fprintf(stderr,"Could not find file size to cache client..!\nUnable to serve client\n"); fclose(pf); return 0; }
         //-----------------------
         //----------------------

        *width=w; *height=h;
        if (pixels==0) {  pixels= (unsigned char*) malloc(w*h*(*bytesPerPixel)*(*channels)*sizeof(char)); }

        if ( pixels != 0 )
        {
          size_t rd = fread(pixels,*bytesPerPixel*(*channels), w*h, pf);
          if (rd < w*h )
             {
               fprintf(stderr,"Note : Incomplete read while reading file %s (%u instead of %u)\n",filename,(unsigned int) rd, w*h);
               fprintf(stderr,"Dimensions ( %u x %u ) , Depth %u bytes , Channels %u \n",w,h,*bytesPerPixel,*channels);
             }

          fclose(pf);

           #if PRINT_COMMENTS
             if ( (*channels==1) && (*bytesPerPixel==2) && (timestamp!=0) ) { printf("DEPTH %lu\n",*timestamp); } else
             if ( (*channels==3) && (*bytesPerPixel==1) && (timestamp!=0) ) { printf("COLOR %lu\n",*timestamp); }
           #endif

          return pixels;
        } else
        {
            fprintf(stderr,"Could not Allocate enough memory for file %s \n",filename);
        }
        fclose(pf);
    } else
    {
      fprintf(stderr,"File %s does not exist \n",filename);
    }
  return buffer;
}

int savePNM(const char * filename,void * pixels , unsigned int width , unsigned int height , unsigned int channels , unsigned int bitsperchannel)
{
    if(pixels==0) { fprintf(stderr,"saveRawImageToFileOGLR(%s) called for an unallocated (empty) frame , will not write any file output\n",filename); return 0; }
    FILE *fd=0;
    fd = fopen(filename,"wb");

    if (bitsperchannel>16) fprintf(stderr,"PNM does not support more than 2 bytes per pixel..!\n");
    if (fd!=0)
    {
        unsigned int n;
        if (channels==3) fprintf(fd, "P6\n");
        else if (channels==1) fprintf(fd, "P5\n");
        else
        {
            fprintf(stderr,"Invalid channels arg (%u) for SaveRawImageToFile\n",channels);
            fclose(fd);
            return 1;
        }

        fprintf(fd, "%u %u\n%u\n", width, height , simplePow(2 ,bitsperchannel)-1);

        float tmp_n = (float) bitsperchannel/ 8;
        tmp_n = tmp_n *  width * height * channels ;
        n = (unsigned int) tmp_n;

        fwrite(pixels, 1 , n , fd);
        fwrite(pixels, 1 , n , fd);
        fflush(fd);
        fclose(fd);
        return 1;
    }
    else
    {
        fprintf(stderr,"SaveRawImageToFile could not open output file %s\n",filename);
        return 0;
    }
    return 0;
}


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



int processPNM(unsigned char * buffer,const char * filename,unsigned int width,unsigned int height,unsigned int channels)
{
  if (buffer!=0)
  {
  unsigned int pixelChannelIndex = 0;
  for (int y=0; y<height; y++)
   {
     for (int x=0; x<width; x++)
      {
         char r = buffer[pixelChannelIndex + 0];
         char g = buffer[pixelChannelIndex + 1];
         char b = buffer[pixelChannelIndex + 2];

         //Simple filter to make image monochrome
         int averageColor = (r + g + b)/3;

         buffer[pixelChannelIndex + 0] = (char) averageColor; //Write back our new R value
         buffer[pixelChannelIndex + 1] = (char) averageColor; //Write back our new G value
         buffer[pixelChannelIndex + 2] = (char) averageColor; //Write back our new B value
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
      unsigned int width=0;
      unsigned int height=0;
      unsigned long timestamp=0;
      unsigned int bytesPerPixel=0;
      unsigned int channels=0;

      unsigned char * pixelsInMemory = ReadPNM(0,filename,&width,&height,&timestamp,&bytesPerPixel,&channels);
      if (pixelsInMemory!=0)
        {
          fprintf(stderr,"Just loaded %s \n",filename);
          fprintf(stderr," It looks like it is %ux%u:%u dimensions \n",width,height,channels);

          int result = processPNM(pixelsInMemory,filename,width,height,channels);

          snprintf(outputFilename,512,"%s-processed.pnm",filename);
          savePNM(outputFilename,pixelsInMemory,width,height,channels,bytesPerPixel*8);

          snprintf(outputFilename,512,"%s.txt",filename);
          writeClassificationOutput(outputFilename,result);


          free(pixelsInMemory);
        }
   }


}
