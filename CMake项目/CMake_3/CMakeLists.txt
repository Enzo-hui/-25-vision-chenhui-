# Disable in-source builds to prevent source tree corruption.
if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(
        FATAL_ERROR 
        "FATAL: In-source builds are not allowed.
        You should create a separate directory for build files."
    )
endif()

# 最小版本号 3.16
cmake_minimum_required(VERSION 3.16)

# 项目名 MySRVL
project(MySRVL)

# ----------------------------------------------------------------------------
#  Parameter configure & generate 参数配置与生成
# ----------------------------------------------------------------------------
option(BUILD_TESTS "build test" ON)
option(BUILD_EXAMPLES "build example" ON)
# ----------------------------------------------------------------------------
#  SRVL compile configure and options 配置编译选项
# ----------------------------------------------------------------------------
# (删掉这行话，在这里开始写)

# ----------------------------------------------------------------------------
#  Get actual SRVL version number from sources 版本控制
# ----------------------------------------------------------------------------
# (删掉这行话，在这里开始写)

# ----------------------------------------------------------------------------
#  Process subdirectories 执行子目录构建
# ----------------------------------------------------------------------------
add_subdirectory(modules)

# ----------------------------------------------------------------------------
#  SRVL Examples
# ----------------------------------------------------------------------------
if(BUILD_EXAMPLES)
    add_subdirectory(samples)
endif(BUILD_EXAMPLES)

message(STATUS "General configuration for SRVL (${SRVL_VERSION})")

