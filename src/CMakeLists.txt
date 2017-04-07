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
  plotter.h
  install_option.h
)

ADD_DEFINITIONS(${GTK3_CFLAGS_OTHER})

set(CMAKE_CC_FLAGS "-rdynamic -Wall")

add_library(math1 math1.c)
add_library(stringutils stringutils.c)
add_library(function function.c)

if (INSTALL)
  add_library(install_option install_option1.c)
else()
  add_library(install_option install_option2.c)
endif()

target_link_libraries(function math1)

add_executable(Plotter plotter.c)
target_link_libraries(Plotter
  ${GTK3_LIBRARIES}

  m
  stringutils
  math1
  function
  install_option
)

if (INSTALL)
  install (TARGETS Plotter DESTINATION /usr/local/bin)
  file (COPY plotter.svg DESTINATION /usr/local/share/icons)
  file(COPY plotter.glade DESTINATION /var/lib/plotter)

  file(WRITE plotter.desktop "[Desktop Entry]
  Type=Application
  Encoding=UTF-8
  Name=Function Plotter
  Exec=Plotter
  Icon=/usr/local/share/icons/plotter.svg
  Terminal=false"
  FILE_PERMISSIONS WORLD_READ WORLD_WRITE)

  file (COPY plotter.desktop DESTINATION /usr/share/applications)
  file (REMOVE
    CMakeFiles
    cmake_install.cmake

    src/CMakeFiles
    src/cmake_install.cmake
    bin
    lib
    )
else ()
  file (COPY plotter.glade DESTINATION ${Function_Plotter_BINARY_DIR}/bin)
endif()
