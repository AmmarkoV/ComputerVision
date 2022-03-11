#! /usr/bin/octave -qf
 
function writeImageToFile(loadedImage, filename)
%https://www.mathworks.com/help/matlab/ref/imwrite.html?s_tid=doc_ta
imwrite(loadedImage,filename);
endfunction
