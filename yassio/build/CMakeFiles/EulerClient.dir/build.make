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
CMAKE_SOURCE_DIR = /home/yassir/Desktop/Yassio/yassio

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yassir/Desktop/Yassio/yassio/build

# Include any dependencies generated for this target.
include CMakeFiles/EulerClient.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/EulerClient.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/EulerClient.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/EulerClient.dir/flags.make

CMakeFiles/EulerClient.dir/src/EulerClient.cpp.o: CMakeFiles/EulerClient.dir/flags.make
CMakeFiles/EulerClient.dir/src/EulerClient.cpp.o: ../src/EulerClient.cpp
CMakeFiles/EulerClient.dir/src/EulerClient.cpp.o: CMakeFiles/EulerClient.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yassir/Desktop/Yassio/yassio/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/EulerClient.dir/src/EulerClient.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/EulerClient.dir/src/EulerClient.cpp.o -MF CMakeFiles/EulerClient.dir/src/EulerClient.cpp.o.d -o CMakeFiles/EulerClient.dir/src/EulerClient.cpp.o -c /home/yassir/Desktop/Yassio/yassio/src/EulerClient.cpp

CMakeFiles/EulerClient.dir/src/EulerClient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/EulerClient.dir/src/EulerClient.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yassir/Desktop/Yassio/yassio/src/EulerClient.cpp > CMakeFiles/EulerClient.dir/src/EulerClient.cpp.i

CMakeFiles/EulerClient.dir/src/EulerClient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/EulerClient.dir/src/EulerClient.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yassir/Desktop/Yassio/yassio/src/EulerClient.cpp -o CMakeFiles/EulerClient.dir/src/EulerClient.cpp.s

# Object files for target EulerClient
EulerClient_OBJECTS = \
"CMakeFiles/EulerClient.dir/src/EulerClient.cpp.o"

# External object files for target EulerClient
EulerClient_EXTERNAL_OBJECTS =

EulerClient: CMakeFiles/EulerClient.dir/src/EulerClient.cpp.o
EulerClient: CMakeFiles/EulerClient.dir/build.make
EulerClient: CMakeFiles/EulerClient.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yassir/Desktop/Yassio/yassio/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable EulerClient"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/EulerClient.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/EulerClient.dir/build: EulerClient
.PHONY : CMakeFiles/EulerClient.dir/build

CMakeFiles/EulerClient.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/EulerClient.dir/cmake_clean.cmake
.PHONY : CMakeFiles/EulerClient.dir/clean

CMakeFiles/EulerClient.dir/depend:
	cd /home/yassir/Desktop/Yassio/yassio/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yassir/Desktop/Yassio/yassio /home/yassir/Desktop/Yassio/yassio /home/yassir/Desktop/Yassio/yassio/build /home/yassir/Desktop/Yassio/yassio/build /home/yassir/Desktop/Yassio/yassio/build/CMakeFiles/EulerClient.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/EulerClient.dir/depend

