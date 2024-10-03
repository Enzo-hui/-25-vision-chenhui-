cmake_minimum_required(VERSION 3.11)
set(CXX_STANDARD 20)

project(DisplayImage)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_subdirectory(Armor)

add_executable( test main.cpp )

target_link_libraries( test ${OpenCV_LIBS} Armor)