set(src_files
    mem.cpp
    memory/transient_heap.cpp
)

add_library(${PROJECT_NAME} ${src_files})
target_include_directories(${PROJECT_NAME} PUBLIC include)

