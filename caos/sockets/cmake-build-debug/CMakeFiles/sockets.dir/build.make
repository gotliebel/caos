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
CMAKE_SOURCE_DIR = /tmp/sockets

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /tmp/sockets/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/sockets.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/sockets.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/sockets.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sockets.dir/flags.make

CMakeFiles/sockets.dir/tcp-client.c.o: CMakeFiles/sockets.dir/flags.make
CMakeFiles/sockets.dir/tcp-client.c.o: /tmp/sockets/tcp-client.c
CMakeFiles/sockets.dir/tcp-client.c.o: CMakeFiles/sockets.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/sockets/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/sockets.dir/tcp-client.c.o"
	/usr/bin/clang-14 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/sockets.dir/tcp-client.c.o -MF CMakeFiles/sockets.dir/tcp-client.c.o.d -o CMakeFiles/sockets.dir/tcp-client.c.o -c /tmp/sockets/tcp-client.c

CMakeFiles/sockets.dir/tcp-client.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sockets.dir/tcp-client.c.i"
	/usr/bin/clang-14 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /tmp/sockets/tcp-client.c > CMakeFiles/sockets.dir/tcp-client.c.i

CMakeFiles/sockets.dir/tcp-client.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sockets.dir/tcp-client.c.s"
	/usr/bin/clang-14 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /tmp/sockets/tcp-client.c -o CMakeFiles/sockets.dir/tcp-client.c.s

# Object files for target sockets
sockets_OBJECTS = \
"CMakeFiles/sockets.dir/tcp-client.c.o"

# External object files for target sockets
sockets_EXTERNAL_OBJECTS =

sockets: CMakeFiles/sockets.dir/tcp-client.c.o
sockets: CMakeFiles/sockets.dir/build.make
sockets: CMakeFiles/sockets.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/tmp/sockets/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable sockets"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sockets.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sockets.dir/build: sockets
.PHONY : CMakeFiles/sockets.dir/build

CMakeFiles/sockets.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sockets.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sockets.dir/clean

CMakeFiles/sockets.dir/depend:
	cd /tmp/sockets/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /tmp/sockets /tmp/sockets /tmp/sockets/cmake-build-debug /tmp/sockets/cmake-build-debug /tmp/sockets/cmake-build-debug/CMakeFiles/sockets.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sockets.dir/depend

