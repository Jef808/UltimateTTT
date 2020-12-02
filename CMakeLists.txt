cmake_minimum_required(VERSION 3.16)

project(UltimateTTT)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_CXX_FLAGS "-std=c++17 -g")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++-10")

set(DCMAKE_VERBOSE_MAKEFILE:BOOL=ON)

file(GLOB
  SOURCES
  ${CMAKE_SOURCE_DIR}/*.cpp
  )

list(FILTER SOURCES EXCLUDE REGEX ".*test.*")
list(FILTER SOURCES EXCLUDE REGEX ".*main.cpp")

file(GLOB
  HEADERS
  ${CMAKE_SOURCE_DIR}/*.hpp
  )

add_library(ttt ${SOURCES})

add_executable(main main.cpp)
target_link_libraries(main ttt)

