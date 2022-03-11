#! /usr/bin/octave -qf
function loadedImage = readImageFromFile(filename)
%https://www.mathworks.com/help/matlab/ref/imread.html?searchHighlight=imread&s_tid=srchtitle_imread_1
loadedImage = imread(filename);
endfunction

function writeImageToFile(loadedImage, filename)
%https://www.mathworks.com/help/matlab/ref/imwrite.html?s_tid=doc_ta
imwrite(loadedImage,filename);
endfunction

function writeResult(filename,result)
 fp = fopen(filename,'w');
 fprintf(fp,"%u\n",result);
 fclose(fp);
endfunction

function processed_image = processImage(loadedImage)
[height width channels] = size(loadedImage);
processed_image = loadedImage;
  for y = 1:height;
   for x = 1:width;
      r = loadedImage(y,x,1);
      g = loadedImage(y,x,2);
      b = loadedImage(y,x,3);
      
      averageColor = (r + g + b) / 3;
      
      processed_image(y,x,1) = averageColor;
      processed_image(y,x,2) = averageColor;
      processed_image(y,x,3) = averageColor;
   endfor     
  endfor
endfunction




printf("%s", program_name());
arg_list = argv();
for i = 1:nargin
    filename = arg_list{i};
    
    printf(" Reading Image %s \n", filename);
    loadedImage = readImageFromFile(filename);
    
    [height width channels] = size(loadedImage);
    printf(" Reading Image %ux%u:%u \n",width,height,channels);
    
    printf(" Processing Image %s \n", filename);
    processed_image = processImage(loadedImage);
    
    printf(" Writing Image %s \n", filename);
    writeImageToFile(processed_image,strcat(filename,"_processed.jpg"));
     
    printf(" Writing Result %s \n", filename);
    writeResult(strcat(filename,".txt"),1);
end