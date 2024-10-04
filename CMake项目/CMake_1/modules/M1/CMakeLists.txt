add_library(M1 src/M1.cpp)
target_include_directories( M1 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(M1 PUBLIC A1 )
