add_library(Math src/Math.cpp)
target_include_directories(Math PUBLIC include)
target_link_libraries( Math ${OpenCV_LIBS} )
