CMAKE_MINIMUM_REQUIRED(VERSION 3.25.1)
project(bl)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(src_files 
"scratchallocator.cpp"
)

set(include_dirs "include")

add_library(${PROJECT_NAME} STATIC ${src_files})
target_include_directories(${PROJECT_NAME} PUBLIC ${include_dirs})
