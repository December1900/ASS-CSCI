# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/december/Desktop/lab03

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/december/Desktop/lab03/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/lab03_7.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/lab03_7.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lab03_7.dir/flags.make

CMakeFiles/lab03_7.dir/task7.cpp.o: CMakeFiles/lab03_7.dir/flags.make
CMakeFiles/lab03_7.dir/task7.cpp.o: ../task7.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/december/Desktop/lab03/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/lab03_7.dir/task7.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lab03_7.dir/task7.cpp.o -c /Users/december/Desktop/lab03/task7.cpp

CMakeFiles/lab03_7.dir/task7.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lab03_7.dir/task7.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/december/Desktop/lab03/task7.cpp > CMakeFiles/lab03_7.dir/task7.cpp.i

CMakeFiles/lab03_7.dir/task7.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lab03_7.dir/task7.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/december/Desktop/lab03/task7.cpp -o CMakeFiles/lab03_7.dir/task7.cpp.s

# Object files for target lab03_7
lab03_7_OBJECTS = \
"CMakeFiles/lab03_7.dir/task7.cpp.o"

# External object files for target lab03_7
lab03_7_EXTERNAL_OBJECTS =

lab03_7: CMakeFiles/lab03_7.dir/task7.cpp.o
lab03_7: CMakeFiles/lab03_7.dir/build.make
lab03_7: CMakeFiles/lab03_7.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/december/Desktop/lab03/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable lab03_7"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lab03_7.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lab03_7.dir/build: lab03_7

.PHONY : CMakeFiles/lab03_7.dir/build

CMakeFiles/lab03_7.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lab03_7.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lab03_7.dir/clean

CMakeFiles/lab03_7.dir/depend:
	cd /Users/december/Desktop/lab03/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/december/Desktop/lab03 /Users/december/Desktop/lab03 /Users/december/Desktop/lab03/cmake-build-debug /Users/december/Desktop/lab03/cmake-build-debug /Users/december/Desktop/lab03/cmake-build-debug/CMakeFiles/lab03_7.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lab03_7.dir/depend

