project( OpenCVExample ) 
#cmake_minimum_required( VERSION 2.8.7 )   
cmake_minimum_required(VERSION 3.5)
find_package(OpenCV REQUIRED)
if (OpenCV_FOUND)
  add_definitions(-DUSE_OPENCV)
  MESSAGE("OpenCV code found and will be used..")   
  MESSAGE(${OpenCV_DIR})   
ENDIF(OpenCV_FOUND)

 

INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})


add_executable(webcamOpenCVTest webcam.cpp)   
target_link_libraries(webcamOpenCVTest rt dl m ${OpenCV_LIBRARIES}    )
set_target_properties(webcamOpenCVTest PROPERTIES 
                       ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
                       LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
                       RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
                      )


add_executable(exampleCPPOpenCV mainOpenCV.cpp)   
target_link_libraries(exampleCPPOpenCV rt dl m ${OpenCV_LIBRARIES}    )
set_target_properties(exampleCPPOpenCV PROPERTIES 
                       ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
                       LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
                       RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
                      )

