# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/chen/华南虎视觉/考核项目/CMake项目/CMake_II

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/chen/华南虎视觉/考核项目/CMake项目/CMake_II/build

# Utility rule file for singleton.

# Include any custom commands dependencies for this target.
include common/singleton/CMakeFiles/singleton.dir/compiler_depend.make

# Include the progress variables for this target.
include common/singleton/CMakeFiles/singleton.dir/progress.make

singleton: common/singleton/CMakeFiles/singleton.dir/build.make
.PHONY : singleton

# Rule to build all files generated by this target.
common/singleton/CMakeFiles/singleton.dir/build: singleton
.PHONY : common/singleton/CMakeFiles/singleton.dir/build

common/singleton/CMakeFiles/singleton.dir/clean:
	cd /home/chen/华南虎视觉/考核项目/CMake项目/CMake_II/build/common/singleton && $(CMAKE_COMMAND) -P CMakeFiles/singleton.dir/cmake_clean.cmake
.PHONY : common/singleton/CMakeFiles/singleton.dir/clean

common/singleton/CMakeFiles/singleton.dir/depend:
	cd /home/chen/华南虎视觉/考核项目/CMake项目/CMake_II/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chen/华南虎视觉/考核项目/CMake项目/CMake_II /home/chen/华南虎视觉/考核项目/CMake项目/CMake_II/common/singleton /home/chen/华南虎视觉/考核项目/CMake项目/CMake_II/build /home/chen/华南虎视觉/考核项目/CMake项目/CMake_II/build/common/singleton /home/chen/华南虎视觉/考核项目/CMake项目/CMake_II/build/common/singleton/CMakeFiles/singleton.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : common/singleton/CMakeFiles/singleton.dir/depend

