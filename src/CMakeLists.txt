CMAKE_MINIMUM_REQUIRED(VERSION 3.25.1)
project(bl)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(src_files 
"linearallocator.cpp"
)

set(include_dirs "include")

if(${DEV_BUILD})
  set(CMAKE_BINARY_DIR "bin/dev/")
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
  add_compile_options("-g")
  add_executable(${PROJECT_NAME} ${src_files} "../test/test.cpp")
else()
  set(CMAKE_BINARY_DIR "bin/release/")
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
  add_library(${PROJECT_NAME} STATIC ${src_files})
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ${include_dirs})
