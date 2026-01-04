cmake_minimum_required(VERSION 4.0.2)
project(bk)

set(SRC_FILES
    mem.cpp
    virtualallocator.cpp
)

option(BK_DEV_CHECK_INLINE "enables debug inline checking utils" OFF)
option(BK_BUILD_DEBUG OFF)
option(BK_BUILD_DEV OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

message("Current source dir: ${CMAKE_CURRENT_SOURCE_DIR}")

set(INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include")

set(ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/..")

#platform specific
# if (WIN32)
#   list(APPEND CXX_FLAGS "-mavx" "-mavx2")
#   if(MSVC OR "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" AND CMAKE_BUILD_TYPE STREQUAL "Debug")
#         # Clang-MSVC: emit CodeView (PDB) debug info
#         list(APPEND CXX_FLAGS -gcodeview)
#   endif()
# endif()


# if (APPLE)
#   if (CMAKE_BUILD_TYPE STREQUAL "Debug")
#     # Other compilers: DWARF debug info
#     list(APPEND CXX_FLAGS -g3)
#   endif()
# endif()
 

if(BK_BUILD_DEV)
  if(BK_DEV_CHECK_INLINE)
    message("Debug inline information enabled.")
    list(APPEND CXX_FLAGS -finline-functions)
    list(APPEND CXX_FLAGS -Rpass=inline)
  endif()
    list(APPEND SRC_FILES ../test/test.cpp)
    list(APPEND INCLUDE_DIRS "${ROOT_DIR}/test/headers/doctest")
    # list(APPEND CXX_FLAGS "-O0")
    add_executable(${PROJECT_NAME} ${SRC_FILES})
else()
  add_library(${PROJECT_NAME} STATIC ${SRC_FILES})
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})
target_compile_options(${PROJECT_NAME} PUBLIC ${CXX_FLAGS})

# if(CMAKE_BUILD_TYPE STREQUAL "Debug" AND (MSVC OR "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang"))
#     target_link_options(${PROJECT_NAME} PRIVATE /DEBU
# endif()

