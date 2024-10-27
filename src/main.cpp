#include <iostream>
#include <map>
#include <vector>
#include <string>

std::map<std::string, std::string> parseArgs(int argc, char* argv[], std::vector<std::string>& positional) {
    std::map<std::string, std::string> options;

    for(int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if(arg[0] == '-') {
            std::string value = "";

            // check if there is a value for the option
            if(i+1 < argc && argv[i+1][0] != '_') {
                value = argv[i+1];
            }
            options[arg] = value; // store option and value
        } else {
            // otherwise, it is a positional argument
            positional.push_back(arg);
        }
    }
    return options;
}

int main(int argc, char* argv[]) {
    std::map<std::string, std::string> options = parseArgs(argc, argv);

    if(options.count("--help") || options.count("-h")) {
        std::cout << "genogrove: A C++ library for the Interval B+ Tree (IBPTree) data structure" << std::endl;
        std::cout << "Usage: genogrove [OPTIONS]" << std::endl;
        std::cout << "Options:" << std::endl;
        std::cout << "    -h, --help: Print this help message" << std::endl;
        std::cout << "    -v, --version: Print the version of genogrove" << std::endl;
        return 0;
    }



}