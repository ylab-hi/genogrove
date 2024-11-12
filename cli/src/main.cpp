// Standard
#include <iostream>
#include <cxxopts.hpp>

// Class
#include "genogrove/all.hpp"

int main(int argc, char** argv) {
    cxxopts::Options options("genogrove", "A C++ library for the Interval B+ Tree (IBPTree) data structure");
    options.add_options()
            ("subcall", "The subcommand to be executed", cxxopts::value<std::string>())
            ("h, help", "Print help")
            ("v, version", "Print version")
            ;
    options.parse_positional({"subcall"});

    // parse the command line arguments
    auto args = options.parse(argc, argv);
    if(args.count("help")) {
        std::cout << options.help() << std::endl;
    }
}

