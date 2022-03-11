#! /usr/bin/octave -qf

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
