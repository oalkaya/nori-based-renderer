# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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

# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/tbb_p

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/tbb_p-build

# Include any dependencies generated for this target.
include CMakeFiles/tbbmalloc_proxy.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/tbbmalloc_proxy.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/tbbmalloc_proxy.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tbbmalloc_proxy.dir/flags.make

CMakeFiles/tbbmalloc_proxy.dir/src/tbbmalloc/proxy.cpp.o: CMakeFiles/tbbmalloc_proxy.dir/flags.make
CMakeFiles/tbbmalloc_proxy.dir/src/tbbmalloc/proxy.cpp.o: /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/tbb_p/src/tbbmalloc/proxy.cpp
CMakeFiles/tbbmalloc_proxy.dir/src/tbbmalloc/proxy.cpp.o: CMakeFiles/tbbmalloc_proxy.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/tbb_p-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tbbmalloc_proxy.dir/src/tbbmalloc/proxy.cpp.o"
	/Applications/Xcode_14_01.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/tbbmalloc_proxy.dir/src/tbbmalloc/proxy.cpp.o -MF CMakeFiles/tbbmalloc_proxy.dir/src/tbbmalloc/proxy.cpp.o.d -o CMakeFiles/tbbmalloc_proxy.dir/src/tbbmalloc/proxy.cpp.o -c /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/tbb_p/src/tbbmalloc/proxy.cpp

CMakeFiles/tbbmalloc_proxy.dir/src/tbbmalloc/proxy.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tbbmalloc_proxy.dir/src/tbbmalloc/proxy.cpp.i"
	/Applications/Xcode_14_01.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/tbb_p/src/tbbmalloc/proxy.cpp > CMakeFiles/tbbmalloc_proxy.dir/src/tbbmalloc/proxy.cpp.i

CMakeFiles/tbbmalloc_proxy.dir/src/tbbmalloc/proxy.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tbbmalloc_proxy.dir/src/tbbmalloc/proxy.cpp.s"
	/Applications/Xcode_14_01.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/tbb_p/src/tbbmalloc/proxy.cpp -o CMakeFiles/tbbmalloc_proxy.dir/src/tbbmalloc/proxy.cpp.s

CMakeFiles/tbbmalloc_proxy.dir/src/tbbmalloc/tbb_function_replacement.cpp.o: CMakeFiles/tbbmalloc_proxy.dir/flags.make
CMakeFiles/tbbmalloc_proxy.dir/src/tbbmalloc/tbb_function_replacement.cpp.o: /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/tbb_p/src/tbbmalloc/tbb_function_replacement.cpp
CMakeFiles/tbbmalloc_proxy.dir/src/tbbmalloc/tbb_function_replacement.cpp.o: CMakeFiles/tbbmalloc_proxy.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/tbb_p-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/tbbmalloc_proxy.dir/src/tbbmalloc/tbb_function_replacement.cpp.o"
	/Applications/Xcode_14_01.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/tbbmalloc_proxy.dir/src/tbbmalloc/tbb_function_replacement.cpp.o -MF CMakeFiles/tbbmalloc_proxy.dir/src/tbbmalloc/tbb_function_replacement.cpp.o.d -o CMakeFiles/tbbmalloc_proxy.dir/src/tbbmalloc/tbb_function_replacement.cpp.o -c /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/tbb_p/src/tbbmalloc/tbb_function_replacement.cpp

CMakeFiles/tbbmalloc_proxy.dir/src/tbbmalloc/tbb_function_replacement.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tbbmalloc_proxy.dir/src/tbbmalloc/tbb_function_replacement.cpp.i"
	/Applications/Xcode_14_01.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/tbb_p/src/tbbmalloc/tbb_function_replacement.cpp > CMakeFiles/tbbmalloc_proxy.dir/src/tbbmalloc/tbb_function_replacement.cpp.i

CMakeFiles/tbbmalloc_proxy.dir/src/tbbmalloc/tbb_function_replacement.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tbbmalloc_proxy.dir/src/tbbmalloc/tbb_function_replacement.cpp.s"
	/Applications/Xcode_14_01.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/tbb_p/src/tbbmalloc/tbb_function_replacement.cpp -o CMakeFiles/tbbmalloc_proxy.dir/src/tbbmalloc/tbb_function_replacement.cpp.s

# Object files for target tbbmalloc_proxy
tbbmalloc_proxy_OBJECTS = \
"CMakeFiles/tbbmalloc_proxy.dir/src/tbbmalloc/proxy.cpp.o" \
"CMakeFiles/tbbmalloc_proxy.dir/src/tbbmalloc/tbb_function_replacement.cpp.o"

# External object files for target tbbmalloc_proxy
tbbmalloc_proxy_EXTERNAL_OBJECTS =

libtbbmalloc_proxy.a: CMakeFiles/tbbmalloc_proxy.dir/src/tbbmalloc/proxy.cpp.o
libtbbmalloc_proxy.a: CMakeFiles/tbbmalloc_proxy.dir/src/tbbmalloc/tbb_function_replacement.cpp.o
libtbbmalloc_proxy.a: CMakeFiles/tbbmalloc_proxy.dir/build.make
libtbbmalloc_proxy.a: CMakeFiles/tbbmalloc_proxy.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/tbb_p-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libtbbmalloc_proxy.a"
	$(CMAKE_COMMAND) -P CMakeFiles/tbbmalloc_proxy.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tbbmalloc_proxy.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tbbmalloc_proxy.dir/build: libtbbmalloc_proxy.a
.PHONY : CMakeFiles/tbbmalloc_proxy.dir/build

CMakeFiles/tbbmalloc_proxy.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tbbmalloc_proxy.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tbbmalloc_proxy.dir/clean

CMakeFiles/tbbmalloc_proxy.dir/depend:
	cd /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/tbb_p-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/tbb_p /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/tbb_p /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/tbb_p-build /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/tbb_p-build /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/tbb_p-build/CMakeFiles/tbbmalloc_proxy.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tbbmalloc_proxy.dir/depend

