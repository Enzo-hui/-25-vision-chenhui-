set(singleton_INCLUDE_DIR)
list(APPEND singleton_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include")

set(singleton_INCLUDE_DIRS ${singleton_INCLUDE_DIR}
                        CACHE PATH "singleton include directories")

add_library(singleton INTERFACE include/robotlab/singleton.hpp)