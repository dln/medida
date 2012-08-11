cmake_minimum_required (VERSION 2.8.3)

## Project Metadata

project (medida)
set (medida_VERSION_MAJOR 0)
set (medida_VERSION_MINOR 1)
set (medida_VERSION_PATCH 0)
set (medida_VERSION_TAG "")
set (medida_VERSION "${medida_VERSION_MAJOR}.${medida_VERSION_MINOR}.${medida_VERSION_PATCH}${medida_VERSION_TAG}")

## Configuration

if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++0x -Wall -Wno-long-long -Wno-deprecated -fno-strict-aliasing")

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  include(FindPkgConfig)
endif()

find_package(Threads REQUIRED)

set(medida_SOURCES
  src/medida/counter.cc
  src/medida/ewma.cc
  src/medida/exp_decay_sample.cc
  src/medida/snapshot.cc
  src/medida/uniform_sample.cc
)

set(medida_HEADERS
  src/medida/medida.h
  src/medida/counter.h
  src/medida/ewma.h
  src/medida/exp_decay_sample.h
  src/medida/sample.h
  src/medida/snapshot.h
  src/medida/uniform_sample.h
)

include_directories(
  ${medida_SOURCE_DIR}/src
  ${medida_BINARY_DIR}
)

add_library(medida SHARED
  ${medida_SOURCES}
  ${medida_PROTO_SRCS}
)

target_link_libraries(medida
  ${CMAKE_THREAD_LIBS_INIT}
  glog
)

set_target_properties(medida PROPERTIES
  OUTPUT_NAME medida
  VERSION ${medida_VERSION}
  SOVERSION ${medida_VERSION_MAJOR}
)

install(TARGETS medida
  LIBRARY DESTINATION lib
)

install(FILES ${medida_HEADERS}
  DESTINATION include/medida/
)

set(PKGCONFIG_FILE ${medida_BINARY_DIR}/medida.pc)
configure_file(medida.pc.cmake ${PKGCONFIG_FILE} @ONLY)
install(FILES ${PKGCONFIG_FILE}
  DESTINATION lib/pkgconfig
)

enable_testing()
add_subdirectory(test)
