# genogrove

[![CMake Multi Platform](https://github.com/ylab-hi/genogrove/actions/workflows/cmake-multi-platform.yml/badge.svg)](https://github.com/ylab-hi/genogrove/actions/workflows/cmake-multi-platform.yml)

Interval B+ Tree (IBPTree) C++ Library

## Install

At first, install genogrove from source. For that, download the source code by either cloning the repository or download a release
```
    git clone https://github.com/ylab-hi/genogrove.git
```

In the source directory, create a build directory and navigate to it
```
    cd genogrove
    mkdir build
    cd build
```
Next, configure the build by running cmake
```
    cmake -S . -B build
    cmake --build build 
```
And finally, install the library by running
``` 
    cmake --install build 
```
Optioanlly, you can specify a custom installation directory by adding the option `--prefix <desired/install/path>` to the install command.

## Usage

Include the genogrove header file in your source code
```
    #include "genogrove/all.hpp"
```






