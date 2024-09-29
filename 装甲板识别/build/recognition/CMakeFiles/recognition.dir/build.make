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
CMAKE_SOURCE_DIR = /home/chen/华南虎视觉/考核项目/装甲板识别

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/chen/华南虎视觉/考核项目/装甲板识别/build

# Include any dependencies generated for this target.
include recognition/CMakeFiles/recognition.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include recognition/CMakeFiles/recognition.dir/compiler_depend.make

# Include the progress variables for this target.
include recognition/CMakeFiles/recognition.dir/progress.make

# Include the compile flags for this target's objects.
include recognition/CMakeFiles/recognition.dir/flags.make

recognition/CMakeFiles/recognition.dir/src/recognition.cpp.o: recognition/CMakeFiles/recognition.dir/flags.make
recognition/CMakeFiles/recognition.dir/src/recognition.cpp.o: ../recognition/src/recognition.cpp
recognition/CMakeFiles/recognition.dir/src/recognition.cpp.o: recognition/CMakeFiles/recognition.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chen/华南虎视觉/考核项目/装甲板识别/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object recognition/CMakeFiles/recognition.dir/src/recognition.cpp.o"
	cd /home/chen/华南虎视觉/考核项目/装甲板识别/build/recognition && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT recognition/CMakeFiles/recognition.dir/src/recognition.cpp.o -MF CMakeFiles/recognition.dir/src/recognition.cpp.o.d -o CMakeFiles/recognition.dir/src/recognition.cpp.o -c /home/chen/华南虎视觉/考核项目/装甲板识别/recognition/src/recognition.cpp

recognition/CMakeFiles/recognition.dir/src/recognition.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/recognition.dir/src/recognition.cpp.i"
	cd /home/chen/华南虎视觉/考核项目/装甲板识别/build/recognition && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chen/华南虎视觉/考核项目/装甲板识别/recognition/src/recognition.cpp > CMakeFiles/recognition.dir/src/recognition.cpp.i

recognition/CMakeFiles/recognition.dir/src/recognition.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/recognition.dir/src/recognition.cpp.s"
	cd /home/chen/华南虎视觉/考核项目/装甲板识别/build/recognition && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chen/华南虎视觉/考核项目/装甲板识别/recognition/src/recognition.cpp -o CMakeFiles/recognition.dir/src/recognition.cpp.s

# Object files for target recognition
recognition_OBJECTS = \
"CMakeFiles/recognition.dir/src/recognition.cpp.o"

# External object files for target recognition
recognition_EXTERNAL_OBJECTS =

recognition/librecognition.a: recognition/CMakeFiles/recognition.dir/src/recognition.cpp.o
recognition/librecognition.a: recognition/CMakeFiles/recognition.dir/build.make
recognition/librecognition.a: recognition/CMakeFiles/recognition.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chen/华南虎视觉/考核项目/装甲板识别/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library librecognition.a"
	cd /home/chen/华南虎视觉/考核项目/装甲板识别/build/recognition && $(CMAKE_COMMAND) -P CMakeFiles/recognition.dir/cmake_clean_target.cmake
	cd /home/chen/华南虎视觉/考核项目/装甲板识别/build/recognition && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/recognition.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
recognition/CMakeFiles/recognition.dir/build: recognition/librecognition.a
.PHONY : recognition/CMakeFiles/recognition.dir/build

recognition/CMakeFiles/recognition.dir/clean:
	cd /home/chen/华南虎视觉/考核项目/装甲板识别/build/recognition && $(CMAKE_COMMAND) -P CMakeFiles/recognition.dir/cmake_clean.cmake
.PHONY : recognition/CMakeFiles/recognition.dir/clean

recognition/CMakeFiles/recognition.dir/depend:
	cd /home/chen/华南虎视觉/考核项目/装甲板识别/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chen/华南虎视觉/考核项目/装甲板识别 /home/chen/华南虎视觉/考核项目/装甲板识别/recognition /home/chen/华南虎视觉/考核项目/装甲板识别/build /home/chen/华南虎视觉/考核项目/装甲板识别/build/recognition /home/chen/华南虎视觉/考核项目/装甲板识别/build/recognition/CMakeFiles/recognition.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : recognition/CMakeFiles/recognition.dir/depend

