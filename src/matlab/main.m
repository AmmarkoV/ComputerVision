#! /usr/bin/octave -qf
 
 
function ans=main()
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
endfor
endfunction