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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/david/Bureau/projets/cpp/CPPTools

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/david/Bureau/projets/cpp/CPPTools/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/main.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/main.dir/flags.make

tests/CMakeFiles/main.dir/main.cpp.o: tests/CMakeFiles/main.dir/flags.make
tests/CMakeFiles/main.dir/main.cpp.o: ../tests/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/david/Bureau/projets/cpp/CPPTools/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/main.dir/main.cpp.o"
	cd /home/david/Bureau/projets/cpp/CPPTools/build/tests && /usr/bin/g++-9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/main.cpp.o -c /home/david/Bureau/projets/cpp/CPPTools/tests/main.cpp

tests/CMakeFiles/main.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/main.cpp.i"
	cd /home/david/Bureau/projets/cpp/CPPTools/build/tests && /usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/david/Bureau/projets/cpp/CPPTools/tests/main.cpp > CMakeFiles/main.dir/main.cpp.i

tests/CMakeFiles/main.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/main.cpp.s"
	cd /home/david/Bureau/projets/cpp/CPPTools/build/tests && /usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/david/Bureau/projets/cpp/CPPTools/tests/main.cpp -o CMakeFiles/main.dir/main.cpp.s

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/main.cpp.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

tests/main: tests/CMakeFiles/main.dir/main.cpp.o
tests/main: tests/CMakeFiles/main.dir/build.make
tests/main: tests/CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/david/Bureau/projets/cpp/CPPTools/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable main"
	cd /home/david/Bureau/projets/cpp/CPPTools/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/main.dir/build: tests/main

.PHONY : tests/CMakeFiles/main.dir/build

tests/CMakeFiles/main.dir/clean:
	cd /home/david/Bureau/projets/cpp/CPPTools/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/main.dir/clean

tests/CMakeFiles/main.dir/depend:
	cd /home/david/Bureau/projets/cpp/CPPTools/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/david/Bureau/projets/cpp/CPPTools /home/david/Bureau/projets/cpp/CPPTools/tests /home/david/Bureau/projets/cpp/CPPTools/build /home/david/Bureau/projets/cpp/CPPTools/build/tests /home/david/Bureau/projets/cpp/CPPTools/build/tests/CMakeFiles/main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/main.dir/depend

