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
CMAKE_SOURCE_DIR = /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build

# Utility rule file for IlmBase_p.

# Include any custom commands dependencies for this target.
include CMakeFiles/IlmBase_p.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/IlmBase_p.dir/progress.make

CMakeFiles/IlmBase_p: CMakeFiles/IlmBase_p-complete

CMakeFiles/IlmBase_p-complete: ext_build/src/IlmBase_p-stamp/IlmBase_p-install
CMakeFiles/IlmBase_p-complete: ext_build/src/IlmBase_p-stamp/IlmBase_p-mkdir
CMakeFiles/IlmBase_p-complete: ext_build/src/IlmBase_p-stamp/IlmBase_p-download
CMakeFiles/IlmBase_p-complete: ext_build/src/IlmBase_p-stamp/IlmBase_p-update
CMakeFiles/IlmBase_p-complete: ext_build/src/IlmBase_p-stamp/IlmBase_p-patch
CMakeFiles/IlmBase_p-complete: ext_build/src/IlmBase_p-stamp/IlmBase_p-configure
CMakeFiles/IlmBase_p-complete: ext_build/src/IlmBase_p-stamp/IlmBase_p-build
CMakeFiles/IlmBase_p-complete: ext_build/src/IlmBase_p-stamp/IlmBase_p-install
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Completed 'IlmBase_p'"
	/Applications/CMake.app/Contents/bin/cmake -E make_directory /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/CMakeFiles
	/Applications/CMake.app/Contents/bin/cmake -E touch /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/CMakeFiles/IlmBase_p-complete
	/Applications/CMake.app/Contents/bin/cmake -E touch /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/IlmBase_p-stamp/IlmBase_p-done

ext_build/src/IlmBase_p-stamp/IlmBase_p-build: ext_build/src/IlmBase_p-stamp/IlmBase_p-configure
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Performing build step for 'IlmBase_p'"
	cd /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/IlmBase_p-build && $(MAKE)
	cd /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/IlmBase_p-build && /Applications/CMake.app/Contents/bin/cmake -E touch /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/IlmBase_p-stamp/IlmBase_p-build

ext_build/src/IlmBase_p-stamp/IlmBase_p-configure: ext_build/tmp/IlmBase_p-cfgcmd.txt
ext_build/src/IlmBase_p-stamp/IlmBase_p-configure: ext_build/src/IlmBase_p-stamp/IlmBase_p-patch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Performing configure step for 'IlmBase_p'"
	cd /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/IlmBase_p-build && /Applications/CMake.app/Contents/bin/cmake -DCMAKE_BUILD_TYPE=Release "-DCMAKE_GENERATOR=Unix Makefiles" -Wno-dev -DCMAKE_INSTALL_PREFIX=/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/dist -DCMAKE_OSX_DEPLOYMENT_TARGET=12 -DCMAKE_OSX_SYSROOT=/Applications/Xcode_14_01.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX12.sdk -DBUILD_SHARED_LIBS=OFF -DNAMESPACE_VERSIONING=NO "-GUnix Makefiles" /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/IlmBase_p
	cd /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/IlmBase_p-build && /Applications/CMake.app/Contents/bin/cmake -E touch /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/IlmBase_p-stamp/IlmBase_p-configure

ext_build/src/IlmBase_p-stamp/IlmBase_p-download: ext_build/src/IlmBase_p-stamp/IlmBase_p-urlinfo.txt
ext_build/src/IlmBase_p-stamp/IlmBase_p-download: ext_build/src/IlmBase_p-stamp/IlmBase_p-mkdir
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Performing download step (DIR copy) for 'IlmBase_p'"
	cd /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src && /Applications/CMake.app/Contents/bin/cmake -E rm -rf /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/IlmBase_p
	cd /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src && /Applications/CMake.app/Contents/bin/cmake -E copy_directory /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/ext/openexr/IlmBase /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/IlmBase_p
	cd /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src && /Applications/CMake.app/Contents/bin/cmake -E touch /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/IlmBase_p-stamp/IlmBase_p-download

ext_build/src/IlmBase_p-stamp/IlmBase_p-install: ext_build/src/IlmBase_p-stamp/IlmBase_p-build
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Performing install step for 'IlmBase_p'"
	cd /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/IlmBase_p-build && $(MAKE) install
	cd /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/IlmBase_p-build && /Applications/CMake.app/Contents/bin/cmake -E touch /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/IlmBase_p-stamp/IlmBase_p-install

ext_build/src/IlmBase_p-stamp/IlmBase_p-mkdir:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Creating directories for 'IlmBase_p'"
	/Applications/CMake.app/Contents/bin/cmake -Dcfgdir= -P /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/tmp/IlmBase_p-mkdirs.cmake
	/Applications/CMake.app/Contents/bin/cmake -E touch /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/IlmBase_p-stamp/IlmBase_p-mkdir

ext_build/src/IlmBase_p-stamp/IlmBase_p-patch: ext_build/src/IlmBase_p-stamp/IlmBase_p-update
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "No patch step for 'IlmBase_p'"
	/Applications/CMake.app/Contents/bin/cmake -E echo_append
	/Applications/CMake.app/Contents/bin/cmake -E touch /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/IlmBase_p-stamp/IlmBase_p-patch

ext_build/src/IlmBase_p-stamp/IlmBase_p-update: ext_build/src/IlmBase_p-stamp/IlmBase_p-download
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "No update step for 'IlmBase_p'"
	/Applications/CMake.app/Contents/bin/cmake -E echo_append
	/Applications/CMake.app/Contents/bin/cmake -E touch /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/ext_build/src/IlmBase_p-stamp/IlmBase_p-update

IlmBase_p: CMakeFiles/IlmBase_p
IlmBase_p: CMakeFiles/IlmBase_p-complete
IlmBase_p: ext_build/src/IlmBase_p-stamp/IlmBase_p-build
IlmBase_p: ext_build/src/IlmBase_p-stamp/IlmBase_p-configure
IlmBase_p: ext_build/src/IlmBase_p-stamp/IlmBase_p-download
IlmBase_p: ext_build/src/IlmBase_p-stamp/IlmBase_p-install
IlmBase_p: ext_build/src/IlmBase_p-stamp/IlmBase_p-mkdir
IlmBase_p: ext_build/src/IlmBase_p-stamp/IlmBase_p-patch
IlmBase_p: ext_build/src/IlmBase_p-stamp/IlmBase_p-update
IlmBase_p: CMakeFiles/IlmBase_p.dir/build.make
.PHONY : IlmBase_p

# Rule to build all files generated by this target.
CMakeFiles/IlmBase_p.dir/build: IlmBase_p
.PHONY : CMakeFiles/IlmBase_p.dir/build

CMakeFiles/IlmBase_p.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/IlmBase_p.dir/cmake_clean.cmake
.PHONY : CMakeFiles/IlmBase_p.dir/clean

CMakeFiles/IlmBase_p.dir/depend:
	cd /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build /Users/daphnemayor/Desktop/ComputerGraphics/nori_omer_daphne/build/CMakeFiles/IlmBase_p.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/IlmBase_p.dir/depend

