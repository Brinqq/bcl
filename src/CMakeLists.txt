cmake_minimum_required(VERSION 4.0.2)
project(bl)

set(SRC_FILES
    mem.cpp
    virtualallocator.cpp
)

set(CMAKE_CXX_STANDARD 20)

option(CHECK_INLINE "enables debug inline checking utils" OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/..")
set(BIN_DIR "${ROOT_DIR}/build/bin/${CMAKE_BUILD_TYPE}")
set(LIB_DIR "${ROOT_DIR}/lib")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BIN_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BIN_DIR})

set(CXX_FLAGS "-Wall" "-mavx" "-mavx2")

#platform specific
if (WIN32)
  if(MSVC OR "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" AND CMAKE_BUILD_TYPE STREQUAL "Debug")
        # Clang-MSVC: emit CodeView (PDB) debug info
        list(APPEND CXX_FLAGS -gcodeview)
  endif()
endif()


if (APPLE)
  if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    # Other compilers: DWARF debug info
    list(APPEND CXX_FLAGS -g3)
  endif()
endif()
 

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  if(CHECK_INLINE)
    message("Debug inline information enabled.")
    list(APPEND CXX_FLAGS -finline-functions)
    list(APPEND CXX_FLAGS -Rpass=inline)
  endif()
    list(APPEND SRC_FILES ../test/test.cpp)
    list(APPEND CXX_FLAGS "-O0")
    add_executable(${PROJECT_NAME} ${SRC_FILES})
else()
  add_library(${PROJECT_NAME} STATIC ${SRC_FILES})
  set(CXX_FLAGS "${CXX_FLAGS} -O2")
endif()

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})
target_compile_options(${PROJECT_NAME} PRIVATE ${CXX_FLAGS})

# if(CMAKE_BUILD_TYPE STREQUAL "Debug" AND (MSVC OR "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang"))
#     target_link_options(${PROJECT_NAME} PRIVATE /DEBU
# endif()

