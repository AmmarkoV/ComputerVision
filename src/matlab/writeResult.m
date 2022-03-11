#! /usr/bin/octave -qf

function writeResult(filename,result)
 fp = fopen(filename,'w');
 fprintf(fp,"%u\n",result);
 fclose(fp);
endfunction
