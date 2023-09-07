cmake_minimum_required(VERSION 3.0)

 

project(trees)

find_package(OpenCV REQUIRED)

find_package(PCL 1.10 REQUIRED)

 

 

include_directories(${PCL_INCLUDE_DIRS} )

link_directories(${PCL_LIBRARY_DIRS} )

add_definitions(${PCL_DEFINITIONS} )

 

add_executable (trees 3D_image_using_PCL.cpp)

target_link_libraries (trees ${PCL_LIBRARIES} ${OpenCV_LIBS})