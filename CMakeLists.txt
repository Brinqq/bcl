cmake_minimum_required(VERSION 4.0.2)
project(bk)

option(BK_BUILD_TEST OFF)
option(BK_BUILD_SAMPLES OFF)
option(BK_BUILD_DEV OFF)

if(PROJECT_IS_TOP_LEVEL)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
  set(CMAKE_CXX_STANDARD 23)
endif()

if(BK_BUILD_DEV)
  add_subdirectory(dev)
endif()

if(BK_BUILD_SAMPLES)
  add_subdirectory(samples)
endif()

if(BK_BUILD_TEST)
  add_subdirectory(test)
endif()

add_subdirectory(src)
