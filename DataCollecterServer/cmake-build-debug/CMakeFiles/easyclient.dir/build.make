# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/mylord/bin/clion-2017.3/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/mylord/bin/clion-2017.3/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mylord/Program/ClionProject/DataCollecterServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mylord/Program/ClionProject/DataCollecterServer/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/easyclient.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/easyclient.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/easyclient.dir/flags.make

CMakeFiles/easyclient.dir/easyclient.o: CMakeFiles/easyclient.dir/flags.make
CMakeFiles/easyclient.dir/easyclient.o: ../easyclient.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mylord/Program/ClionProject/DataCollecterServer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/easyclient.dir/easyclient.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/easyclient.dir/easyclient.o -c /home/mylord/Program/ClionProject/DataCollecterServer/easyclient.cpp

CMakeFiles/easyclient.dir/easyclient.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/easyclient.dir/easyclient.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mylord/Program/ClionProject/DataCollecterServer/easyclient.cpp > CMakeFiles/easyclient.dir/easyclient.i

CMakeFiles/easyclient.dir/easyclient.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/easyclient.dir/easyclient.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mylord/Program/ClionProject/DataCollecterServer/easyclient.cpp -o CMakeFiles/easyclient.dir/easyclient.s

CMakeFiles/easyclient.dir/easyclient.o.requires:

.PHONY : CMakeFiles/easyclient.dir/easyclient.o.requires

CMakeFiles/easyclient.dir/easyclient.o.provides: CMakeFiles/easyclient.dir/easyclient.o.requires
	$(MAKE) -f CMakeFiles/easyclient.dir/build.make CMakeFiles/easyclient.dir/easyclient.o.provides.build
.PHONY : CMakeFiles/easyclient.dir/easyclient.o.provides

CMakeFiles/easyclient.dir/easyclient.o.provides.build: CMakeFiles/easyclient.dir/easyclient.o


# Object files for target easyclient
easyclient_OBJECTS = \
"CMakeFiles/easyclient.dir/easyclient.o"

# External object files for target easyclient
easyclient_EXTERNAL_OBJECTS =

easyclient: CMakeFiles/easyclient.dir/easyclient.o
easyclient: CMakeFiles/easyclient.dir/build.make
easyclient: CMakeFiles/easyclient.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mylord/Program/ClionProject/DataCollecterServer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable easyclient"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/easyclient.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/easyclient.dir/build: easyclient

.PHONY : CMakeFiles/easyclient.dir/build

CMakeFiles/easyclient.dir/requires: CMakeFiles/easyclient.dir/easyclient.o.requires

.PHONY : CMakeFiles/easyclient.dir/requires

CMakeFiles/easyclient.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/easyclient.dir/cmake_clean.cmake
.PHONY : CMakeFiles/easyclient.dir/clean

CMakeFiles/easyclient.dir/depend:
	cd /home/mylord/Program/ClionProject/DataCollecterServer/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mylord/Program/ClionProject/DataCollecterServer /home/mylord/Program/ClionProject/DataCollecterServer /home/mylord/Program/ClionProject/DataCollecterServer/cmake-build-debug /home/mylord/Program/ClionProject/DataCollecterServer/cmake-build-debug /home/mylord/Program/ClionProject/DataCollecterServer/cmake-build-debug/CMakeFiles/easyclient.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/easyclient.dir/depend

