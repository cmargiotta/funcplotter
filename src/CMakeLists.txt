cmake_minimum_required (VERSION 2.6)

include_directories(${Function_Plotter_SOURCE_DIR}/src)

set(Function_Plotter_HEADERS
  ${GTK3_INCLUDE_DIRS}

  extvar.h
  math1.h
  stringutils.h
  function.h
  plotter.h
)

add_library(math1 math1.c)
add_library(stringutils stringutils.c)
add_library(function function.c)
target_link_libraries(function math1)

gresource(${CMAKE_CURRENT_SOURCE_DIR} plotter.gresource.xml ${CMAKE_BINARY_DIR} resources)
add_library(resources ${CMAKE_BINARY_DIR}/resources.c)

add_executable(Plotter plotter.c)
target_include_directories(Plotter PUBLIC ${CMAKE_BINARY_DIR})
target_link_libraries(Plotter
  ${GTK3_LIBRARIES}

  m
  stringutils
  math1
  function
  resources
)

install (TARGETS Plotter DESTINATION bin)
install (FILES plotter.svg DESTINATION share/icons)
install (FILES plotter.desktop DESTINATION share/applications)
