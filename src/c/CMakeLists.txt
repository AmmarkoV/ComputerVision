project( exampleInC ) 
cmake_minimum_required( VERSION 2.8.7 )
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake/modules ${CMAKE_MODULE_PATH})
   
#PNM Only example
add_executable( 
               exampleInC_PNMOnly 
               mainSimplePNMOnly.c 
              )
target_link_libraries(exampleInC_PNMOnly rt m ) 
set_target_properties(exampleInC_PNMOnly PROPERTIES 
                       ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
                       LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
                       RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
                      )

#Example with JPEG/PNG Codecs
add_definitions(-DUSE_JPG_FILES=1)
add_definitions(-DUSE_PNG_FILES=1)
add_executable( 
               exampleInC_Codec 
               mainCodecs.c
               Codecs/asciiInput.c 
               Codecs/bmpInput.c
               Codecs/codecs.c
               Codecs/jpgExifexternal.c
               Codecs/jpgExiforient_embed.c
               Codecs/jpgInput.c
               Codecs/pfmInput.c
               Codecs/pngInput.c
               Codecs/ppmInput.c
              )
target_link_libraries(exampleInC_Codec rt m jpeg png ) 
set_target_properties(exampleInC_Codec PROPERTIES 
                       ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
                       LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
                       RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
                      )
