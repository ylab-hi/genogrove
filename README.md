# genogrove

[![CMake Multi Platform](https://github.com/ylab-hi/genogrove/actions/workflows/cmake-multi-platform.yml/badge.svg)](https://github.com/ylab-hi/genogrove/actions/workflows/cmake-multi-platform.yml)
[![Downloads](https://img.shields.io/github/downloads/ylab-hi/genogrove/total.svg)](https://img.shields.io/github/downloads/ylab-hi/genogrove/total.svg)
[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](http://www.gnu.org/licenses/gpl-3.0)

Interval B+ Tree (IBPTree) C++ Library

## Install

At first, install genogrove from source. For that, download the source code by either cloning the repository or download a release
```
    git clone https://github.com/ylab-hi/genogrove.git
```

In the source directory, create a build directory and navigate to it
```
    cd genogrove
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






