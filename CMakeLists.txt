cmake_minimum_required(VERSION 4.0.2)
project(bk)

option(BK_DEV OFF)

if(PROJECT_IS_TOP_LEVEL)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif()

if(BK_DEV)
  add_subdirectory(dev)
  # add_subdirectory(test)
endif()

add_subdirectory(src)
