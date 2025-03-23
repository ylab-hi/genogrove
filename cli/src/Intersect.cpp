#include "Intersect.hpp"

cxxopts::Options Intersect::parseArgs(int argc, char** argv) {
    cxxopts::Options options("index", "Index an Interval File");
    options.add_options()
            ("-q, queryfile", "The query file to be indexed",
             cxxopts::value<std::string>())
            ("-t, targetfile", "The target file to be index/searched against",
                    cxxopts::value<std::string>())
            ("-o, outputfile", "Write the index to the specified file",
             cxxopts::value<std::string>()->default_value(""))
            ("k, order", "The order of the tree (default: 3)",
             cxxopts::value<int>()->default_value("3"))
            ;
    options.parse_positional({"inputfile"});
    return options;
}


void Intersect::execute(const cxxopts::ParseResult& args) {
    if(args.count("inputfile")) {
        std::string inputfile = args["inputfile"].as<std::string>();
        std::cout << "Indexing file: " << inputfile << std::endl;
    }

    if(args.count("outputfile")) {
        std::string outputfile = args["outputfile"].as<std::string>();
        std::cout << "Writing index to file: " << outputfile << std::endl;
    }
}