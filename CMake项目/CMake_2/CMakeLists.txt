cmake_minimum_required(VERSION 3.10)

project(test)

set(CMAKE_CXX_STANDARD 20)
find_package( OpenCV REQUIRED )
find_package(Threads REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} ${singleton_INCLUDE_DIRS} )
link_libraries( ${OpenCV_LIBS} )
# # # # 以下内容禁止修改 # # # #
option(BUILD_A "build modules a" ON)
option(BUILD_B "build modules b" OFF)
option(BUILD_TESTS "build tests" OFF)

if(BUILD_TESTS)
    enable_testing()
endif()

add_subdirectory(modules)
add_subdirectory(common)
# 小提示: module2 需要用到 pthread，即 target_link_libraries(xxx pthread)
# # # # 以上内容禁止修改 # # # #


if(BUILD_A)
    add_definitions(-DWITH_A)
endif()

if(BUILD_B)
    add_definitions(-DWITH_B)
endif()
add_executable(server server.cpp)
add_executable(client client.cpp)

target_link_libraries(server PUBLIC rmath assembly1 module2 module1 singleton)
target_link_libraries(client PUBLIC module2 module1)

# target_compile_definitions(server PUBLIC WITH_A)
