cmake_minimum_required(VERSION 2.8.8)

PROJECT(Core)

find_package(Qt5Widgets)
find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5Network)
find_package(Qt5Multimedia)
find_package(Qt5Sql)

SET(MLS_SOURCES 
./src/encoder/iencoder.cpp
./src/global/global.cpp
./src/global/value.cpp
./src/global/json.cpp
./src/global/json_value.cpp
./src/global/plugin.cpp
./src/global/ring_buffer.cpp
./src/global/runtime.cpp
./src/global/escape_call_server.cpp
./src/global/settings.cpp
./src/gui/gui_channel.cpp
./src/gui/gui_config.cpp
./src/gui/gui_encoder.cpp
./src/gui/gui_login.cpp
./src/gui/gui_main.cpp
./src/gui/gui_main_scene.cpp
./src/gui/gui_main_source.cpp
./src/gui/gui_surface_settings.cpp
./src/gui/gui_updater.cpp
./src/source/source.cpp
./src/channel/ichannel.cpp
./src/channel/read_pipe.cpp
./src/channel/rtmp_channel.cpp
./src/channel/write_pipe.cpp
./src/channel/local_recording.cpp
./src/channel/rtmp_proxy.cpp
./src/render/opengl_surface.cpp
./src/render/irender_widget.cpp
./src/render/isurface.cpp
./src/render/opengl_render_widget.cpp
./src/main_mls.cpp
./src/source/gl_source.cpp
../mls_inc/escape_call.h
)

SET(MLS_GUIS ./src/ui/mqs_configuration.ui
./src/ui/mqs_encoder.ui
./src/ui/mqs_login.ui
./src/ui/mqs_main.ui
./src/ui/mqs_surface_settings.ui
./src/ui/mqs_transport.ui
./src/ui/mqs_update.ui)

SET(MLS_RESOURCES ./src/resources/mediaquicksync.qrc)

SET (CMAKE_BUILD_TYPE "Debug")

set(CMAKE_AUTOMOC ON)
QT5_WRAP_UI(MLS_GUIS_UIC ${MLS_GUIS})
QT5_ADD_RESOURCES(MLS_RESOURCES_RCC ${MLS_RESOURCES})

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
./src/gui
./src/encoder
./src/global
./src/source
./src/channel
./src/render
./src/render/glm
./src/render/glew
./src
../mls_inc
)

SET(CMAKE_CXX_FLAGS "-std=gnu++11 -O0 -g3 -ggdb")

ADD_EXECUTABLE(mls WIN32 ${MLS_SOURCES} ${MLS_GUIS_UIC} ${MLS_RESOURCES_RCC} )

TARGET_LINK_LIBRARIES(mls 
${Qt5Widgets_LIBRARIES}
${Qt5Core_LIBRARIES}
${Qt5Gui_LIBRARIES}
${Qt5Network_LIBRARIES}
${Qt5Multimedia_LIBRARIES}
${Qt5Sql_LIBRARIES}
opengl32.lib 
glu32.lib 
pthread
d:/mls-project/core/src/render/glew/libglew32.dll.a
)
