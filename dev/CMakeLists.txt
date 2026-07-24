add_executable(dev entry.cpp)

target_link_directories(dev PRIVATE
  ${CMAKE_LIBRARY_OUTPUT_DIR}
)

target_include_directories(dev PRIVATE
  ../src/include
)
