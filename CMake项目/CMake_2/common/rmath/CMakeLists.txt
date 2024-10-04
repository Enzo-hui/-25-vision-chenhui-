link_libraries( ${OpenCV_LIBS} )
add_library(rmath src/rmath.cpp)
target_include_directories(rmath PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
