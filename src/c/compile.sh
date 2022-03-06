#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$DIR"

gcc mainSimplePNMOnly.c -o ../../exampleInC_PNMOnly

gcc mainCodecs.c Codecs/asciiInput.c Codecs/bmpInput.c Codecs/codecs.c Codecs/jpgExifexternal.c Codecs/jpgExiforient_embed.c Codecs/jpgInput.c Codecs/pfmInput.c Codecs/pngInput.c Codecs/ppmInput.c -DUSE_JPG_FILES=1 -DUSE_PNG_FILES=1 -lpng -ljpeg -o ../../exampleInC_Codec

exit 0
