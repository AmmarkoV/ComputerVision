#! /usr/bin/octave -qf

function loadedImage = readImageFromFile(filename)
%https://www.mathworks.com/help/matlab/ref/imread.html?searchHighlight=imread&s_tid=srchtitle_imread_1
loadedImage = imread(filename);
endfunction
