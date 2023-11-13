cmake_minimum_required( VERSION 2.8 )
project( geometry )

# Add Eigen header file
include_directories( "/usr/include/eigen3" )

add_executable(eigenGeometry eigenGeometry.cpp)
