cmake_minimum_required (VERSION 2.6)
project(Function_Plotter)

if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

include(gresource.cmake)

set( EXECUTABLE_OUTPUT_PATH ${Function_Plotter_BINARY_DIR}/bin )
set( LIBRARY_OUTPUT_PATH ${Function_Plotter_BINARY_DIR}/lib )

FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

ADD_DEFINITIONS(${GTK3_CFLAGS_OTHER})
set(CMAKE_CC_FLAGS "-rdynamic -Wall -lm")


add_subdirectory(src)
