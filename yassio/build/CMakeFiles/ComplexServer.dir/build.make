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
include CMakeFiles/ComplexServer.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ComplexServer.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ComplexServer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ComplexServer.dir/flags.make

CMakeFiles/ComplexServer.dir/src/ComplexServer.cpp.o: CMakeFiles/ComplexServer.dir/flags.make
CMakeFiles/ComplexServer.dir/src/ComplexServer.cpp.o: ../src/ComplexServer.cpp
CMakeFiles/ComplexServer.dir/src/ComplexServer.cpp.o: CMakeFiles/ComplexServer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yassir/Desktop/Yassio/yassio/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ComplexServer.dir/src/ComplexServer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ComplexServer.dir/src/ComplexServer.cpp.o -MF CMakeFiles/ComplexServer.dir/src/ComplexServer.cpp.o.d -o CMakeFiles/ComplexServer.dir/src/ComplexServer.cpp.o -c /home/yassir/Desktop/Yassio/yassio/src/ComplexServer.cpp

CMakeFiles/ComplexServer.dir/src/ComplexServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ComplexServer.dir/src/ComplexServer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yassir/Desktop/Yassio/yassio/src/ComplexServer.cpp > CMakeFiles/ComplexServer.dir/src/ComplexServer.cpp.i

CMakeFiles/ComplexServer.dir/src/ComplexServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ComplexServer.dir/src/ComplexServer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yassir/Desktop/Yassio/yassio/src/ComplexServer.cpp -o CMakeFiles/ComplexServer.dir/src/ComplexServer.cpp.s

# Object files for target ComplexServer
ComplexServer_OBJECTS = \
"CMakeFiles/ComplexServer.dir/src/ComplexServer.cpp.o"

# External object files for target ComplexServer
ComplexServer_EXTERNAL_OBJECTS =

ComplexServer: CMakeFiles/ComplexServer.dir/src/ComplexServer.cpp.o
ComplexServer: CMakeFiles/ComplexServer.dir/build.make
ComplexServer: CMakeFiles/ComplexServer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yassir/Desktop/Yassio/yassio/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ComplexServer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ComplexServer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ComplexServer.dir/build: ComplexServer
.PHONY : CMakeFiles/ComplexServer.dir/build

CMakeFiles/ComplexServer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ComplexServer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ComplexServer.dir/clean

CMakeFiles/ComplexServer.dir/depend:
	cd /home/yassir/Desktop/Yassio/yassio/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yassir/Desktop/Yassio/yassio /home/yassir/Desktop/Yassio/yassio /home/yassir/Desktop/Yassio/yassio/build /home/yassir/Desktop/Yassio/yassio/build /home/yassir/Desktop/Yassio/yassio/build/CMakeFiles/ComplexServer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ComplexServer.dir/depend

