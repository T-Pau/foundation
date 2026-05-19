# T'Pau C++ Kernal

Kernal is a C++ library collecting various classes and functions that are used in other T'Pau projects. It is meant to be included as a Git submodule.  

## Using C++ Kernal

To use this library in another cmake project, add the following lines to the top level `CMakeLists.txt`:

```cmake

add_subdirectory(tpau-cpp-kernal/lib)
set(PACKAGE_AUTHOR "<author name>")
set(PACKAGE_BUGREPORT "<bugreport email address>")
```

Add this lines to your `config.h.in`:

```c++
#define PACKAGE "@CMAKE_PROJECT_NAME@"
#define PACKAGE_BUGREPORT "@PACKAGE_BUGREPORT@"
#define VERSION "@CMAKE_PROJECT_VERSION@"
#define PACKAGE_AUTHOR "@PACKAGE_AUTHOR@"
```

For the programs using the library, add:

```cmake
target_include_directories(${PROGRAM} PRIVATE ${CMAKE_SOURCE_DIR}/tpau-cpp-kernal/lib ${PROJECT_BINARY_DIR})
target_link_libraries(${PROGRAM} tpau-cpp-kernal)
```

## Building C++ Kernal

Kernal is written in C++20.

To build it, you need a C++20 compiler and [cmake](https://cmake.org). To run the tests, you need [Python](https://www.python.org) and [nihtest](https://github.com/nih-at/nihtest).
