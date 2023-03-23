set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp) 
# Note
# It is not recommended to use file(GLOB_RECURSE ...), instead to use set or add_executable
# Examples
# set(SOURCES
#       src/main.cpp
#       src/foo.cpp
#       src/bar.cpp)
# add_executable(ExampleProject main.cpp fool.cpp file1.h)

set(SOURCES ${SOURCES})

add_library(${BINARY}_lib STATIC ${SOURCES})
add_executable(${BINARY}_run ${SOURCES})