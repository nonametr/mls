cmake_minimum_required(VERSION 2.8)
PROJECT(x264_plugin)

add_library (mlsx264 SHARED 
rgb2yuv.cpp 
encoder_export.cpp 
Libx264Encoder.cpp
./mt/thread.cpp
./mt/thread_core.cpp)
 
 INCLUDE_DIRECTORIES(
 ./mt
 ./
 )
 
SET(LIBRARY_OUTPUT_PATH ../Core/plugins)
SET(CMAKE_CXX_FLAGS "-std=gnu++11 -O0 -g3 -ggdb")
TARGET_LINK_LIBRARIES(mlsx264
d:/mls-project/libx264_plugin/x264/libx264.a
pthread)
