// Standard
#include <iostream>
#include "cxxopts.hpp"

// Class
#include "genogrove/all.hpp"
#include "Subcall.hpp"
#include "Index.hpp"
#include "Intersect.hpp"

std::unique_ptr<Subcall> createSubcall(const std::string& subcall) {
    if(subcall == "idx") {
        return std::make_unique<Index>();
    } else if(subcall == "isec") {
        return std::make_unique<Intersect>();
    } else {
        return nullptr;
    }
}

void printGeneralHelp(cxxopts::Options& options) {
    std::cout << options.help() << "\n";
    std::cout << "Available subcommands: \n";
    std::cout << "\tindex:\t\tIndex an Interval File\n";
    std::cout << "\tintersect:\tSearch for interval overlaps in the index\n";
    std::cout << "For more details on a subcommand, use the --help option with the subcommand.\n";
}

int main(int argc, char** argv) {
    cxxopts::Options options("genogrove", "A C++ library for the Interval B+ Tree (Grove) data structure");
    options.add_options()
            ("subcall", "The subcommand to be executed", cxxopts::value<std::string>())
            ("h, help", "Print help")
            ("v, version", "Print version")
            ;
    options.parse_positional({"subcall"});

    // parse the command line arguments
    auto args = options.parse(argc, argv);

    // check if the help option was selected (on the main level)
    if(args.count("help")) {
        if(!args.count("subcall")) {
            printGeneralHelp(options);
            return 0;
        }
    }

    std::string subcall = args["subcall"].as<std::string>();
    std::unique_ptr<Subcall> command = createSubcall(subcall);

    if(!command) {
        std::cerr << "Error: Unknown subcommand '" << subcall << "'.\n";
        std::cerr << options.help() << std::endl;
        return 1;
    }

    // parse additional options for the subcommand
    cxxopts::Options subcallOptions = command->parseArgs(argc -1, argv + 1);
    cxxopts::ParseResult subcallArgs = subcallOptions.parse(argc -1, argv + 1);

    if(subcallArgs.count("help")) {
        std::cout << subcallOptions.help() << "\n";
        return 0;
    }

    command->execute(subcallArgs);
}

