# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Sam/ACMOJ/PPCA/RISC-V/Pipeline-Simulator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Sam/ACMOJ/PPCA/RISC-V/Pipeline-Simulator/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Pipeline_Simulator.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Pipeline_Simulator.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Pipeline_Simulator.dir/flags.make

CMakeFiles/Pipeline_Simulator.dir/main.cpp.o: CMakeFiles/Pipeline_Simulator.dir/flags.make
CMakeFiles/Pipeline_Simulator.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Sam/ACMOJ/PPCA/RISC-V/Pipeline-Simulator/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Pipeline_Simulator.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Pipeline_Simulator.dir/main.cpp.o -c /mnt/c/Sam/ACMOJ/PPCA/RISC-V/Pipeline-Simulator/main.cpp

CMakeFiles/Pipeline_Simulator.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Pipeline_Simulator.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Sam/ACMOJ/PPCA/RISC-V/Pipeline-Simulator/main.cpp > CMakeFiles/Pipeline_Simulator.dir/main.cpp.i

CMakeFiles/Pipeline_Simulator.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Pipeline_Simulator.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Sam/ACMOJ/PPCA/RISC-V/Pipeline-Simulator/main.cpp -o CMakeFiles/Pipeline_Simulator.dir/main.cpp.s

# Object files for target Pipeline_Simulator
Pipeline_Simulator_OBJECTS = \
"CMakeFiles/Pipeline_Simulator.dir/main.cpp.o"

# External object files for target Pipeline_Simulator
Pipeline_Simulator_EXTERNAL_OBJECTS =

Pipeline_Simulator: CMakeFiles/Pipeline_Simulator.dir/main.cpp.o
Pipeline_Simulator: CMakeFiles/Pipeline_Simulator.dir/build.make
Pipeline_Simulator: CMakeFiles/Pipeline_Simulator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Sam/ACMOJ/PPCA/RISC-V/Pipeline-Simulator/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Pipeline_Simulator"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Pipeline_Simulator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Pipeline_Simulator.dir/build: Pipeline_Simulator

.PHONY : CMakeFiles/Pipeline_Simulator.dir/build

CMakeFiles/Pipeline_Simulator.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Pipeline_Simulator.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Pipeline_Simulator.dir/clean

CMakeFiles/Pipeline_Simulator.dir/depend:
	cd /mnt/c/Sam/ACMOJ/PPCA/RISC-V/Pipeline-Simulator/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Sam/ACMOJ/PPCA/RISC-V/Pipeline-Simulator /mnt/c/Sam/ACMOJ/PPCA/RISC-V/Pipeline-Simulator /mnt/c/Sam/ACMOJ/PPCA/RISC-V/Pipeline-Simulator/cmake-build-debug /mnt/c/Sam/ACMOJ/PPCA/RISC-V/Pipeline-Simulator/cmake-build-debug /mnt/c/Sam/ACMOJ/PPCA/RISC-V/Pipeline-Simulator/cmake-build-debug/CMakeFiles/Pipeline_Simulator.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Pipeline_Simulator.dir/depend

