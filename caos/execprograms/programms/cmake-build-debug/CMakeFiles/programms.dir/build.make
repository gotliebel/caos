# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_SOURCE_DIR = /tmp/programms

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /tmp/programms/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/programms.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/programms.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/programms.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/programms.dir/flags.make

CMakeFiles/programms.dir/fourth.c.o: CMakeFiles/programms.dir/flags.make
CMakeFiles/programms.dir/fourth.c.o: /tmp/programms/fourth.c
CMakeFiles/programms.dir/fourth.c.o: CMakeFiles/programms.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/programms/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/programms.dir/fourth.c.o"
	/usr/bin/clang-14 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/programms.dir/fourth.c.o -MF CMakeFiles/programms.dir/fourth.c.o.d -o CMakeFiles/programms.dir/fourth.c.o -c /tmp/programms/fourth.c

CMakeFiles/programms.dir/fourth.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/programms.dir/fourth.c.i"
	/usr/bin/clang-14 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /tmp/programms/fourth.c > CMakeFiles/programms.dir/fourth.c.i

CMakeFiles/programms.dir/fourth.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/programms.dir/fourth.c.s"
	/usr/bin/clang-14 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /tmp/programms/fourth.c -o CMakeFiles/programms.dir/fourth.c.s

# Object files for target programms
programms_OBJECTS = \
"CMakeFiles/programms.dir/fourth.c.o"

# External object files for target programms
programms_EXTERNAL_OBJECTS =

programms: CMakeFiles/programms.dir/fourth.c.o
programms: CMakeFiles/programms.dir/build.make
programms: CMakeFiles/programms.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/tmp/programms/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable programms"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/programms.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/programms.dir/build: programms
.PHONY : CMakeFiles/programms.dir/build

CMakeFiles/programms.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/programms.dir/cmake_clean.cmake
.PHONY : CMakeFiles/programms.dir/clean

CMakeFiles/programms.dir/depend:
	cd /tmp/programms/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /tmp/programms /tmp/programms /tmp/programms/cmake-build-debug /tmp/programms/cmake-build-debug /tmp/programms/cmake-build-debug/CMakeFiles/programms.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/programms.dir/depend
