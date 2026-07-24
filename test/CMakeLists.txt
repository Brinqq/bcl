include(FetchContent)

FetchContent_Declare(
  doctest
  GIT_REPOSITORY https://github.com/doctest/doctest.git
  GIT_TAG master
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/headers/doctest
)

FetchContent_MakeAvailable(doctest)


add_executable(test 
  test.cpp
)

target_include_directories(test PRIVATE 
headers
headers/doctest/
)
