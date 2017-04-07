cmake_minimum_required (VERSION 2.6)

if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

set( EXECUTABLE_OUTPUT_PATH ${Function_Plotter_BINARY_DIR}/bin )
set( LIBRARY_OUTPUT_PATH ${Function_Plotter_BINARY_DIR}/lib )

FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

set(Function_Plotter_HEADERS
  ${GTK3_INCLUDE_DIRS}

  extvar.h
  math1.h
  stringutils.h
  function.h
  plotter.h)

ADD_DEFINITIONS(${GTK3_CFLAGS_OTHER})

set(CMAKE_CC_FLAGS "-rdynamic -Wall")

add_library(math1 math1.c)
add_library(stringutils stringutils.c)
add_library(function function.c)
target_link_libraries(function math1)

add_executable(Plotter plotter.c)
target_link_libraries(Plotter
  ${GTK3_LIBRARIES}

  m
  stringutils
  math1
  function)



install (TARGETS Plotter DESTINATION /usr/local/bin)
file (COPY plotter.svg DESTINATION /usr/local/share/icons)
file(COPY plotter.glade DESTINATION /var/lib/plotter)

file(WRITE plotter.desktop "[Desktop Entry]
Type=Application
Encoding=UTF-8
Name=Function Plotter
Exec=Plotter
Icon=/usr/local/share/icons/plotter.svg
Terminal=false")

file (COPY plotter.desktop DESTINATION /usr/share/applications)
