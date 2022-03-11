#! /usr/bin/octave -qf
    
filesToProcess = [
                  "../../images/dice.png",
                  "../../images/dice.jpg",
                  "../../images/dice.pnm"
                 ]

printf("We have %u arguments\n",size(filesToProcess));
 
for i = 1:size(filesToProcess)
    filename = filesToProcess(i,:);
    
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