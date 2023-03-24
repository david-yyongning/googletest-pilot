# googletest-pilot
googletest pilot project


## C++ project setup with CMake & unit tests (google test)

```
https://raymii.org/s/tutorials/Cpp_project_setup_with_cmake_and_unit_tests.html
```

### Install software (cmake and googletest)
#### cmake
On Windows, you can use MinGW or cygwin to install development tools including CMake. Clion offers a nice GUI for that.
On Linux
```
apt-get install cmake
```
#### Googletest
```
git clone https://github.com/google/googletest/
```
gtest comes with a CMakeLists.txt so integrating it in your project is easy.

### Folder structure (sample)
```
$ tree -L 2 ExampleProject/
ExampleProject/
|-- build/
|-- CMakeLists.txt
|-- lib/
|   `-- googletest 
|-- src/
|   |-- CMakeLists.txt
|   |-- Formula.cpp
|   |-- Formula.h
|   `-- main.cpp
`-- tst/
    |-- CMakeLists.txt
    |-- Formula-test.cpp
    `-- main.cpp
```
Here is a oneliner to create the folders:
```
mkdir -p ExampleProject/{build,lib,src,tst}
```
Copy the googletest repository folder your cloned earlier into the lib/ folder.

### CMakeLists.txt
The file CMakeLists.txt contains a set of directives and instructions describing the project's source files and targets (executable, library, or both). This can get quite complex quite fast, CMake has many options
#### Main folder CMakeLists.txt
```
cmake_minimum_required(VERSION 3.10)
project(ExampleProject)  # set built-in variable CMAKE_PROJECT_NAME as "ExampleProject"

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_subdirectory(src)
add_subdirectory(tst)
add_subdirectory(lib/googletest)
```
#### src folder CMakeLists.txt:
```
set(BINARY ${CMAKE_PROJECT_NAME})

# add all *.h and *.c to SOURCES with recursive directory searching including sub-directories.
# Note
# It is not recommended to use file(GLOB_RECURSE ...), instead to use set or add_executable
# Examples
# set(SOURCES
#       src/main.cpp
#       src/foo.cpp
#       src/bar.cpp)
# add_executable(ExampleProject main.cpp fool.cpp file1.h)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp) 

set(SOURCES ${SOURCES})  # not necessary but could prevent SOURCES being assigned to other values

add_executable(${BINARY}_run ${SOURCES})  # generate executable ${CMAKE_PROJECT_NAME}_run with ${SOURCES} files

add_library(${BINARY}_lib STATIC ${SOURCES}) # generate Static library

```
#### tst folder CMakeLists.txt
```
set(BINARY ${CMAKE_PROJECT_NAME}_tst)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)

set(SOURCES ${TEST_SOURCES})

add_executable(${BINARY} ${TEST_SOURCES})

add_test(NAME ${BINARY} COMMAND ${BINARY})

# specify libraries that the executable should link against, project static library and Google test library gtest

target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest)  
```

### Sample source code and tests

#### Source Code
```
src/main.cpp:

#include <iostream>
#include "Formula.h"

int main()
{
    std::cout << "Bla: " << Formula::bla(2) << std::endl;
    return 0;
}
src/Formula.h:

#ifndef EXAMPLEPROJECT_FORMULA_H
#define EXAMPLEPROJECT_FORMULA_H

class Formula
{
public:
    static int bla(int arg1);
};

#endif //EXAMPLEPROJECT_FORMULA_H

src/Formula.cpp:

#include "Formula.h"
int Formula::bla(int arg1)
{
    return arg1 * 2;
}
```
#### Test code
```
tst/main.cpp:

#include "gtest/gtest.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```
This file will run all the tests and since we recursively included everything with CMake, it will effectively run all tests in all files in this folder.
```
tst/Formula-test.cpp:

#include "gtest/gtest.h"
#include "Formula.h"

TEST(blaTest, test1) {
    //arrange
    //act
    //assert
    EXPECT_EQ (Formula::bla (0),  0);
    EXPECT_EQ (Formula::bla (10), 20);
    EXPECT_EQ (Formula::bla (50), 100);
}
```

### Compile
```
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles" 

Output:
/home/.../build$ cmake .. -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles" 
-- The C compiler identification is GNU 8.3.0
-- The CXX compiler identification is GNU 8.3.0
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Found Python: /home/.../anaconda3/bin/python3 (found version "3.9.7") found components:  Interpreter 
-- Looking for pthread.h
-- Looking for pthread.h - found
-- Looking for pthread_create
-- Looking for pthread_create - not found
-- Looking for pthread_create in pthreads
-- Looking for pthread_create in pthreads - not found
-- Looking for pthread_create in pthread
-- Looking for pthread_create in pthread - found
-- Found Threads: TRUE  
-- Configuring done
-- Generating done
-- Build files have been written to:/home/.../build
```

There are now a bunch of files and folders in the build folder, most important, the Makefile. You can now compile the project:
```
make all

Output:
Scanning dependencies of target ExampleProject_run
[  5%] Building CXX object src/CMakeFiles/ExampleProject_run.dir/Formula.cpp.o
[ 11%] Building CXX object src/CMakeFiles/ExampleProject_run.dir/main.cpp.o
[ 17%] Linking CXX executable ExampleProject_run
[ 17%] Built target ExampleProject_run
Scanning dependencies of target ExampleProject_lib
[ 23%] Building CXX object src/CMakeFiles/ExampleProject_lib.dir/Formula.cpp.o
[ 29%] Building CXX object src/CMakeFiles/ExampleProject_lib.dir/main.cpp.o
[ 35%] Linking CXX static library libExampleProject_lib.a
[ 35%] Built target ExampleProject_lib
Scanning dependencies of target gtest
[ 41%] Building CXX object lib/googletest/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o
[ 47%] Linking CXX static library ../../libgtest.a
[ 47%] Built target gtest
Scanning dependencies of target ExampleProject_tst
[ 52%] Building CXX object tst/CMakeFiles/ExampleProject_tst.dir/Formula-test.cpp.o
[ 58%] Building CXX object tst/CMakeFiles/ExampleProject_tst.dir/main.cpp.o
[ 64%] Linking CXX executable ExampleProject_tst
[ 64%] Built target ExampleProject_tst
Scanning dependencies of target gmock
[ 70%] Building CXX object lib/googletest/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.o
[ 76%] Linking CXX static library ../../libgmock.a
[ 76%] Built target gmock
Scanning dependencies of target gmock_main
[ 82%] Building CXX object lib/googletest/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o
[ 88%] Linking CXX static library ../../libgmock_main.a
[ 88%] Built target gmock_main
Scanning dependencies of target gtest_main
[ 94%] Building CXX object lib/googletest/googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o
[100%] Linking CXX static library ../../libgtest_main.a
[100%] Built target gtest_main
```
You now have two executable files, as defined in the CMakeLists.txt:
```
$ find . -executable -type f
./tst/ExampleProject_tst
./src/ExampleProject_run
```
### Run application and the Unit Test
```
./src/ExampleProject_run

Output:
Bla: 4

./tst/ExampleProject_tst 

Output:
[==========] Running 1 test from 1 test suite.
[----------] Global test environment set-up.
[----------] 1 test from blaTest
[ RUN      ] blaTest.test1
[       OK ] blaTest.test1 (0 ms)
[----------] 1 test from blaTest (0 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test suite ran. (0 ms total)
[  PASSED  ] 1 test.

```
A quick one-liner to compile and run the tests. You can run this whenever you want to re-run the tests (after changing code for example):
```
make ExampleProject_tst; tst/ExampleProject_tst 
```
