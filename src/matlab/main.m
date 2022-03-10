#! /usr/bin/octave -qf
function image = readImage(filename)
image = imread(filename);
endfunction

function writeImage(image, filename)
imwrite(image,filename);
endfunction

function writeResult(filename,result)
 fp = fopen(filename,'w');
 fprintf(fp,"%u\n",result);
 fclose(fp);
endfunction

function processed_image = processImage(image)
[height width channels] = size(image);
processed_image = image;
  for y = 1:height
   for x = 1:width
      r = image(y,x,1);
      g = image(y,x,2);
      b = image(y,x,3);
      
      averageColor = (r + g + b) / 3 ;
      
      processed_image(y,x,1) = averageColor;
      processed_image(y,x,2) = averageColor;
      processed_image(y,x,3) = averageColor;
   endfor     
  endfor
endfunction




printf("%s", program_name());
arg_list = argv();
for i = 1:nargin
    filename = arg_list{i}
    printf(" Reading Image %s \n", filename);
    image = readImage(filename);
    [height width channels] = size(image);
    printf(" Reading Image %ux%u:%u \n",width,height,channels);
    
    printf(" Processing Image %s \n", filename);
    processed_image = processImage(image);
    
    printf(" Writing Image %s \n", filename);
    writeImage(processed_image,strcat(filename,"_processed.jpg"));
     
    printf(" Writing Result %s \n", filename);
    writeResult(strcat(filename,".txt"),1);
end