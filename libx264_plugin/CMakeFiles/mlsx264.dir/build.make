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
CMAKE_COMMAND = "C:\Program Files (x86)\CMake 2.8\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files (x86)\CMake 2.8\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = "C:\Program Files (x86)\CMake 2.8\bin\cmake-gui.exe"

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\mls-project\libx264_plugin

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\mls-project\libx264_plugin

# Include any dependencies generated for this target.
include CMakeFiles/mlsx264.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mlsx264.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mlsx264.dir/flags.make

CMakeFiles/mlsx264.dir/rgb2yuv.cpp.obj: CMakeFiles/mlsx264.dir/flags.make
CMakeFiles/mlsx264.dir/rgb2yuv.cpp.obj: CMakeFiles/mlsx264.dir/includes_CXX.rsp
CMakeFiles/mlsx264.dir/rgb2yuv.cpp.obj: rgb2yuv.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report D:\mls-project\libx264_plugin\CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/mlsx264.dir/rgb2yuv.cpp.obj"
	C:\Qt\Qt5.0.1\Tools\MinGW\bin\g++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles\mlsx264.dir\rgb2yuv.cpp.obj -c D:\mls-project\libx264_plugin\rgb2yuv.cpp

CMakeFiles/mlsx264.dir/rgb2yuv.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mlsx264.dir/rgb2yuv.cpp.i"
	C:\Qt\Qt5.0.1\Tools\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E D:\mls-project\libx264_plugin\rgb2yuv.cpp > CMakeFiles\mlsx264.dir\rgb2yuv.cpp.i

CMakeFiles/mlsx264.dir/rgb2yuv.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mlsx264.dir/rgb2yuv.cpp.s"
	C:\Qt\Qt5.0.1\Tools\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S D:\mls-project\libx264_plugin\rgb2yuv.cpp -o CMakeFiles\mlsx264.dir\rgb2yuv.cpp.s

CMakeFiles/mlsx264.dir/rgb2yuv.cpp.obj.requires:
.PHONY : CMakeFiles/mlsx264.dir/rgb2yuv.cpp.obj.requires

CMakeFiles/mlsx264.dir/rgb2yuv.cpp.obj.provides: CMakeFiles/mlsx264.dir/rgb2yuv.cpp.obj.requires
	$(MAKE) -f CMakeFiles\mlsx264.dir\build.make CMakeFiles/mlsx264.dir/rgb2yuv.cpp.obj.provides.build
.PHONY : CMakeFiles/mlsx264.dir/rgb2yuv.cpp.obj.provides

CMakeFiles/mlsx264.dir/rgb2yuv.cpp.obj.provides.build: CMakeFiles/mlsx264.dir/rgb2yuv.cpp.obj

CMakeFiles/mlsx264.dir/encoder_export.cpp.obj: CMakeFiles/mlsx264.dir/flags.make
CMakeFiles/mlsx264.dir/encoder_export.cpp.obj: CMakeFiles/mlsx264.dir/includes_CXX.rsp
CMakeFiles/mlsx264.dir/encoder_export.cpp.obj: encoder_export.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report D:\mls-project\libx264_plugin\CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/mlsx264.dir/encoder_export.cpp.obj"
	C:\Qt\Qt5.0.1\Tools\MinGW\bin\g++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles\mlsx264.dir\encoder_export.cpp.obj -c D:\mls-project\libx264_plugin\encoder_export.cpp

CMakeFiles/mlsx264.dir/encoder_export.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mlsx264.dir/encoder_export.cpp.i"
	C:\Qt\Qt5.0.1\Tools\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E D:\mls-project\libx264_plugin\encoder_export.cpp > CMakeFiles\mlsx264.dir\encoder_export.cpp.i

CMakeFiles/mlsx264.dir/encoder_export.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mlsx264.dir/encoder_export.cpp.s"
	C:\Qt\Qt5.0.1\Tools\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S D:\mls-project\libx264_plugin\encoder_export.cpp -o CMakeFiles\mlsx264.dir\encoder_export.cpp.s

CMakeFiles/mlsx264.dir/encoder_export.cpp.obj.requires:
.PHONY : CMakeFiles/mlsx264.dir/encoder_export.cpp.obj.requires

CMakeFiles/mlsx264.dir/encoder_export.cpp.obj.provides: CMakeFiles/mlsx264.dir/encoder_export.cpp.obj.requires
	$(MAKE) -f CMakeFiles\mlsx264.dir\build.make CMakeFiles/mlsx264.dir/encoder_export.cpp.obj.provides.build
.PHONY : CMakeFiles/mlsx264.dir/encoder_export.cpp.obj.provides

CMakeFiles/mlsx264.dir/encoder_export.cpp.obj.provides.build: CMakeFiles/mlsx264.dir/encoder_export.cpp.obj

CMakeFiles/mlsx264.dir/Libx264Encoder.cpp.obj: CMakeFiles/mlsx264.dir/flags.make
CMakeFiles/mlsx264.dir/Libx264Encoder.cpp.obj: CMakeFiles/mlsx264.dir/includes_CXX.rsp
CMakeFiles/mlsx264.dir/Libx264Encoder.cpp.obj: Libx264Encoder.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report D:\mls-project\libx264_plugin\CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/mlsx264.dir/Libx264Encoder.cpp.obj"
	C:\Qt\Qt5.0.1\Tools\MinGW\bin\g++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles\mlsx264.dir\Libx264Encoder.cpp.obj -c D:\mls-project\libx264_plugin\Libx264Encoder.cpp

CMakeFiles/mlsx264.dir/Libx264Encoder.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mlsx264.dir/Libx264Encoder.cpp.i"
	C:\Qt\Qt5.0.1\Tools\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E D:\mls-project\libx264_plugin\Libx264Encoder.cpp > CMakeFiles\mlsx264.dir\Libx264Encoder.cpp.i

CMakeFiles/mlsx264.dir/Libx264Encoder.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mlsx264.dir/Libx264Encoder.cpp.s"
	C:\Qt\Qt5.0.1\Tools\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S D:\mls-project\libx264_plugin\Libx264Encoder.cpp -o CMakeFiles\mlsx264.dir\Libx264Encoder.cpp.s

CMakeFiles/mlsx264.dir/Libx264Encoder.cpp.obj.requires:
.PHONY : CMakeFiles/mlsx264.dir/Libx264Encoder.cpp.obj.requires

CMakeFiles/mlsx264.dir/Libx264Encoder.cpp.obj.provides: CMakeFiles/mlsx264.dir/Libx264Encoder.cpp.obj.requires
	$(MAKE) -f CMakeFiles\mlsx264.dir\build.make CMakeFiles/mlsx264.dir/Libx264Encoder.cpp.obj.provides.build
.PHONY : CMakeFiles/mlsx264.dir/Libx264Encoder.cpp.obj.provides

CMakeFiles/mlsx264.dir/Libx264Encoder.cpp.obj.provides.build: CMakeFiles/mlsx264.dir/Libx264Encoder.cpp.obj

CMakeFiles/mlsx264.dir/mt/thread.cpp.obj: CMakeFiles/mlsx264.dir/flags.make
CMakeFiles/mlsx264.dir/mt/thread.cpp.obj: CMakeFiles/mlsx264.dir/includes_CXX.rsp
CMakeFiles/mlsx264.dir/mt/thread.cpp.obj: mt/thread.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report D:\mls-project\libx264_plugin\CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/mlsx264.dir/mt/thread.cpp.obj"
	C:\Qt\Qt5.0.1\Tools\MinGW\bin\g++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles\mlsx264.dir\mt\thread.cpp.obj -c D:\mls-project\libx264_plugin\mt\thread.cpp

CMakeFiles/mlsx264.dir/mt/thread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mlsx264.dir/mt/thread.cpp.i"
	C:\Qt\Qt5.0.1\Tools\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E D:\mls-project\libx264_plugin\mt\thread.cpp > CMakeFiles\mlsx264.dir\mt\thread.cpp.i

CMakeFiles/mlsx264.dir/mt/thread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mlsx264.dir/mt/thread.cpp.s"
	C:\Qt\Qt5.0.1\Tools\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S D:\mls-project\libx264_plugin\mt\thread.cpp -o CMakeFiles\mlsx264.dir\mt\thread.cpp.s

CMakeFiles/mlsx264.dir/mt/thread.cpp.obj.requires:
.PHONY : CMakeFiles/mlsx264.dir/mt/thread.cpp.obj.requires

CMakeFiles/mlsx264.dir/mt/thread.cpp.obj.provides: CMakeFiles/mlsx264.dir/mt/thread.cpp.obj.requires
	$(MAKE) -f CMakeFiles\mlsx264.dir\build.make CMakeFiles/mlsx264.dir/mt/thread.cpp.obj.provides.build
.PHONY : CMakeFiles/mlsx264.dir/mt/thread.cpp.obj.provides

CMakeFiles/mlsx264.dir/mt/thread.cpp.obj.provides.build: CMakeFiles/mlsx264.dir/mt/thread.cpp.obj

CMakeFiles/mlsx264.dir/mt/thread_core.cpp.obj: CMakeFiles/mlsx264.dir/flags.make
CMakeFiles/mlsx264.dir/mt/thread_core.cpp.obj: CMakeFiles/mlsx264.dir/includes_CXX.rsp
CMakeFiles/mlsx264.dir/mt/thread_core.cpp.obj: mt/thread_core.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report D:\mls-project\libx264_plugin\CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/mlsx264.dir/mt/thread_core.cpp.obj"
	C:\Qt\Qt5.0.1\Tools\MinGW\bin\g++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles\mlsx264.dir\mt\thread_core.cpp.obj -c D:\mls-project\libx264_plugin\mt\thread_core.cpp

CMakeFiles/mlsx264.dir/mt/thread_core.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mlsx264.dir/mt/thread_core.cpp.i"
	C:\Qt\Qt5.0.1\Tools\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E D:\mls-project\libx264_plugin\mt\thread_core.cpp > CMakeFiles\mlsx264.dir\mt\thread_core.cpp.i

CMakeFiles/mlsx264.dir/mt/thread_core.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mlsx264.dir/mt/thread_core.cpp.s"
	C:\Qt\Qt5.0.1\Tools\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S D:\mls-project\libx264_plugin\mt\thread_core.cpp -o CMakeFiles\mlsx264.dir\mt\thread_core.cpp.s

CMakeFiles/mlsx264.dir/mt/thread_core.cpp.obj.requires:
.PHONY : CMakeFiles/mlsx264.dir/mt/thread_core.cpp.obj.requires

CMakeFiles/mlsx264.dir/mt/thread_core.cpp.obj.provides: CMakeFiles/mlsx264.dir/mt/thread_core.cpp.obj.requires
	$(MAKE) -f CMakeFiles\mlsx264.dir\build.make CMakeFiles/mlsx264.dir/mt/thread_core.cpp.obj.provides.build
.PHONY : CMakeFiles/mlsx264.dir/mt/thread_core.cpp.obj.provides

CMakeFiles/mlsx264.dir/mt/thread_core.cpp.obj.provides.build: CMakeFiles/mlsx264.dir/mt/thread_core.cpp.obj

# Object files for target mlsx264
mlsx264_OBJECTS = \
"CMakeFiles/mlsx264.dir/rgb2yuv.cpp.obj" \
"CMakeFiles/mlsx264.dir/encoder_export.cpp.obj" \
"CMakeFiles/mlsx264.dir/Libx264Encoder.cpp.obj" \
"CMakeFiles/mlsx264.dir/mt/thread.cpp.obj" \
"CMakeFiles/mlsx264.dir/mt/thread_core.cpp.obj"

# External object files for target mlsx264
mlsx264_EXTERNAL_OBJECTS =

D:/mls-project/Core/plugins/libmlsx264.dll: CMakeFiles/mlsx264.dir/rgb2yuv.cpp.obj
D:/mls-project/Core/plugins/libmlsx264.dll: CMakeFiles/mlsx264.dir/encoder_export.cpp.obj
D:/mls-project/Core/plugins/libmlsx264.dll: CMakeFiles/mlsx264.dir/Libx264Encoder.cpp.obj
D:/mls-project/Core/plugins/libmlsx264.dll: CMakeFiles/mlsx264.dir/mt/thread.cpp.obj
D:/mls-project/Core/plugins/libmlsx264.dll: CMakeFiles/mlsx264.dir/mt/thread_core.cpp.obj
D:/mls-project/Core/plugins/libmlsx264.dll: CMakeFiles/mlsx264.dir/build.make
D:/mls-project/Core/plugins/libmlsx264.dll: x264/libx264.a
D:/mls-project/Core/plugins/libmlsx264.dll: CMakeFiles/mlsx264.dir/objects1.rsp
D:/mls-project/Core/plugins/libmlsx264.dll: CMakeFiles/mlsx264.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library D:\mls-project\Core\plugins\libmlsx264.dll"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\mlsx264.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mlsx264.dir/build: D:/mls-project/Core/plugins/libmlsx264.dll
.PHONY : CMakeFiles/mlsx264.dir/build

CMakeFiles/mlsx264.dir/requires: CMakeFiles/mlsx264.dir/rgb2yuv.cpp.obj.requires
CMakeFiles/mlsx264.dir/requires: CMakeFiles/mlsx264.dir/encoder_export.cpp.obj.requires
CMakeFiles/mlsx264.dir/requires: CMakeFiles/mlsx264.dir/Libx264Encoder.cpp.obj.requires
CMakeFiles/mlsx264.dir/requires: CMakeFiles/mlsx264.dir/mt/thread.cpp.obj.requires
CMakeFiles/mlsx264.dir/requires: CMakeFiles/mlsx264.dir/mt/thread_core.cpp.obj.requires
.PHONY : CMakeFiles/mlsx264.dir/requires

CMakeFiles/mlsx264.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\mlsx264.dir\cmake_clean.cmake
.PHONY : CMakeFiles/mlsx264.dir/clean

CMakeFiles/mlsx264.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\mls-project\libx264_plugin D:\mls-project\libx264_plugin D:\mls-project\libx264_plugin D:\mls-project\libx264_plugin D:\mls-project\libx264_plugin\CMakeFiles\mlsx264.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mlsx264.dir/depend

