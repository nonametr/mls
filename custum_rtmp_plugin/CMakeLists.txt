cmake_minimum_required(VERSION 2.8.8)

PROJECT(custom_rtmp_plugin)

find_package(Qt5Widgets)
find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5Network)
find_package(Qt5Multimedia)
find_package(Qt5Sql)

SET(CUSTOM_RTMP_CHANNEL_SOURCES
./src/channel_export.cpp
./src/global/json_value.cpp
./src/global/json.cpp
./src/custom_rtmp_channel.cpp
./src/read_pipe.cpp
./src/write_pipe.cpp
./src/rtmp_proxy.cpp
./src/global/ring_buffer.cpp
./src/global/global.h
./src/gui/gui_channel.cpp
./src/global/settings.cpp
../mls_inc/escape_call.h
./src/escape_call_client.cpp
)

SET(CUSTOM_RTMP_CHANNEL_GUIS
./src/gui/custom_rtmp_channel.ui
)

SET (CMAKE_BUILD_TYPE "Debug")
set(CMAKE_AUTOMOC ON)
QT5_WRAP_UI(CUSTOM_RTMP_CHANNEL_GUIS_UIC ${CUSTOM_RTMP_CHANNEL_GUIS})

include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${Qt5Core_INCLUDE_DIRS})
include_directories(${Qt5Gui_INCLUDE_DIRS})
include_directories(${Qt5Network_INCLUDE_DIRS})
include_directories(${Qt5Multimedia_INCLUDE_DIRS})
include_directories(${Qt5Sql_INCLUDE_DIRS})
add_definitions(${Qt5Widgets_DEFINITIONS})
add_definitions(${Qt5Core_DEFINITIONS})
add_definitions(${Qt5Gui_DEFINITIONS})
add_definitions(${Qt5Network_DEFINITIONS})
add_definitions(${Qt5Multimedia_DEFINITIONS})
add_definitions(${Qt5Sql_DEFINITIONS})

INCLUDE_DIRECTORIES(
${CMAKE_CURRENT_BINARY_DIR}
./
../mls_inc
./src
./src/global
./src/gui
)

SET(CMAKE_CXX_FLAGS "-std=gnu++11 -O0 -g3 -ggdb")

add_library (mlscustomrtmpchannel SHARED
${CUSTOM_RTMP_CHANNEL_SOURCES}
${CUSTOM_RTMP_CHANNEL_GUIS_UIC}
)

SET(LIBRARY_OUTPUT_PATH ../Core/plugins)

TARGET_LINK_LIBRARIES(mlscustomrtmpchannel
${Qt5Widgets_LIBRARIES}
${Qt5Core_LIBRARIES}
${Qt5Gui_LIBRARIES}
${Qt5Network_LIBRARIES}
${Qt5Multimedia_LIBRARIES}
${Qt5Sql_LIBRARIES}
pthread)
