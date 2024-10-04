# 在此处进行 CMake 设置（最小版本号，项目名）
CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

project(test)

set(CMAKE_CXX_STANDARD 20)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} ${kalman_INCLUDE_DIRS})

####### 以下禁止修改 #######
add_subdirectory(common)   #
add_subdirectory(modules)  #
####### 以上禁止修改 #######

# 在此处生成可执行程序
add_executable(test main.cpp)
# 在此处链接库
target_link_libraries(test M1 M2 Math)