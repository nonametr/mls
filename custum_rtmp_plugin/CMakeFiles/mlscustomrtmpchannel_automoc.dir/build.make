# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 2.8

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "c:\Program Files (x86)\CMake 2.8\bin\cmake.exe"

# The command to remove a file.
RM = "c:\Program Files (x86)\CMake 2.8\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = "C:\Program Files (x86)\CMake 2.8\bin\cmake-gui.exe"

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\mls-project\custum_rtmp_plugin

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\mls-project\custum_rtmp_plugin

# Utility rule file for mlscustomrtmpchannel_automoc.

# Include the progress variables for this target.
include CMakeFiles/mlscustomrtmpchannel_automoc.dir/progress.make

CMakeFiles/mlscustomrtmpchannel_automoc:
	$(CMAKE_COMMAND) -E cmake_progress_report D:\mls-project\custum_rtmp_plugin\CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Automoc for target mlscustomrtmpchannel"
	"c:\Program Files (x86)\CMake 2.8\bin\cmake.exe" -E cmake_automoc D:/mls-project/custum_rtmp_plugin/CMakeFiles/mlscustomrtmpchannel_automoc.dir/

mlscustomrtmpchannel_automoc: CMakeFiles/mlscustomrtmpchannel_automoc
mlscustomrtmpchannel_automoc: CMakeFiles/mlscustomrtmpchannel_automoc.dir/build.make
.PHONY : mlscustomrtmpchannel_automoc

# Rule to build all files generated by this target.
CMakeFiles/mlscustomrtmpchannel_automoc.dir/build: mlscustomrtmpchannel_automoc
.PHONY : CMakeFiles/mlscustomrtmpchannel_automoc.dir/build

CMakeFiles/mlscustomrtmpchannel_automoc.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\mlscustomrtmpchannel_automoc.dir\cmake_clean.cmake
.PHONY : CMakeFiles/mlscustomrtmpchannel_automoc.dir/clean

CMakeFiles/mlscustomrtmpchannel_automoc.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\mls-project\custum_rtmp_plugin D:\mls-project\custum_rtmp_plugin D:\mls-project\custum_rtmp_plugin D:\mls-project\custum_rtmp_plugin D:\mls-project\custum_rtmp_plugin\CMakeFiles\mlscustomrtmpchannel_automoc.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mlscustomrtmpchannel_automoc.dir/depend
