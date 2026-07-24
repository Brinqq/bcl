set(src_files
    mem.cpp
    virtualallocator.cpp
)

add_library(${PROJECT_NAME} ${src_files})
target_include_directories(${PROJECT_NAME} PRIVATE include)

