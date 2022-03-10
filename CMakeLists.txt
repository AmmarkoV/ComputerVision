project( ComputerVisionProject ) 
cmake_minimum_required( VERSION 2.8.7 )

#Build the C examples
add_subdirectory (src/c)

#Build the CPP/OpenCV examples
add_subdirectory (src/cpp)

