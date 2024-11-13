#include "Overlap.hpp"

cxxopts::ParseResult Overlap::parseArgs(int argc, char** argv) {
    cxxopts::Options options("overlap", "Search for interval overlaps in the index");
    options.add_options()
            ("input", "The search string or file to search for",
                    cxxopts::value<std::string>())
            ("o, output", "The output file to store the overlaps",
                    cxxopts::value<std::string>())
            ;
    options.parse_positional({"input"});
    return options.parse(argc, argv);
}

void Overlap::execute(const cxxopts::ParseResult& args) {
    if(args.count("input")) {
        std::string input = args["input"].as<std::string>();
        std::cout << "Searching for overlaps in file: " << input << std::endl;
    }

    if(args.count("output")) {
        std::string output = args["output"].as<std::string>();
        std::cout << "Writing overlaps to file: " << output << std::endl;
    }
}
