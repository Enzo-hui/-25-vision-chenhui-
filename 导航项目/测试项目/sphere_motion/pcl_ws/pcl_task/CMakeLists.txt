cmake_minimum_required(VERSION 3.8)
project(pcl_task)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(rclcpp REQUIRED)
# find_package(PCL REQUIRED COMPONENTS common io)
find_package(PCL REQUIRED )
find_package(pcl_conversions REQUIRED)
# find_package(PCL 1.8 REQUIRED)
include_directories(/opt/ros/humble/include)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})


# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

include_directories(include)

ament_export_include_directories(include)

add_executable(PCD_Publisher src/pcd_loading.cpp)
ament_target_dependencies(PCD_Publisher
  rclcpp
  sensor_msgs
)

add_executable(ros2pcl_test_sub 
  src/ros2pcl_test_sub.cpp
)
ament_target_dependencies(ros2pcl_test_sub
  rclcpp
  sensor_msgs
)

install(TARGETS
  PCD_Publisher
  DESTINATION lib/${PROJECT_NAME}
)
install(TARGETS
  ros2pcl_test_sub
  DESTINATION lib/${PROJECT_NAME}
)
install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME})
target_link_libraries(PCD_Publisher ${PCL_LIBRARIES})
target_include_directories(PCD_Publisher PUBLIC ${pcl_conversions_INCLUDE_DIRS} ) 
target_link_libraries(ros2pcl_test_sub ${PCL_LIBRARIES})
target_include_directories(ros2pcl_test_sub  PUBLIC ${pcl_conversions_INCLUDE_DIRS} ) 
ament_package()

