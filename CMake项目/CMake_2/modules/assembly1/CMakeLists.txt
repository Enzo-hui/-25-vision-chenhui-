add_library(assembly1 src/assembly1.cpp)
target_include_directories(assembly1 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(assembly1_test test/assembly1_test.cpp)
target_link_libraries(assembly1_test assembly1 assembly2)
target_include_directories(assembly1_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_test(NAME assembly1_test COMMAND assembly1_test)