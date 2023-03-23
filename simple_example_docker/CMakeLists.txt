
cmake_minimum_required(VERSION 3.10)
project(ExampleProject C CXX)

set(CMAKE_C_STANDARD 99)  # not critical
set(CMAKE_CXX_STANDARD 14)

include_directories(src)

enable_testing()

add_subdirectory(src)
add_subdirectory(tst)
add_subdirectory(lib/googletest)
