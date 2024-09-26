# genogrove

[![CMake Multi Platform](https://github.com/ylab-hi/genogrove/actions/workflows/cmake-multi-platform.yml/badge.svg)](https://github.com/ylab-hi/genogrove/actions/workflows/cmake-multi-platform.yml)
[![Downloads](https://img.shields.io/github/downloads/ylab-hi/genogrove/total.svg)](https://img.shields.io/github/downloads/ylab-hi/genogrove/total.svg)
[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](http://www.gnu.org/licenses/gpl-3.0)

genogrove is a C++ library for the Interval B+ Tree (IBPTree) data structure. It provides a simple and efficient way to store and search data in a tree-like structure.

## Quick Start

To get started with genogrove, download the source code by either cloning the repository or downloading a release.
In the source directory, configure the build by running cmake:

```
    cmake -S . -B build
    cmake --build build
```
If required, custom compilers can be specified by adding the option `-DCMAKE_CXX_COMPILER=<compiler>` and 
`-DCMAKE_C_COMPILER=<compiler>`. 

Once you have the source code, change to the source directory and install the library by running the following commands:
```
    cmake --install build
```
Optionally, you can specify a custom installation directory by adding the option `--prefix <desired/install/path>` to the
install command.

### Usage

To use the library in your project, include the genogrove header file in your source code:
```
    #include "genogrove/all.hpp"
```

Create an instance of the `IBPTree` class and specify the order of the tree (k):
```
    int k = 3;
    genogrove::IBPTree tree(k);
```

Register the types of the data you want to store in the tree with the `TypeRegistry` (e.g., `int`):
```
    genogrove::TypeRegistry::registerType<int>();
```








