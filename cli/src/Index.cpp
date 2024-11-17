#include "Index.hpp"

cxxopts::Options Index::parseArgs(int argc, char** argv) {
    cxxopts::Options options("genogrove index", "Index an Interval File");
    options.add_options()
            ("inputfile", "The input file to be indexed",
                    cxxopts::value<std::string>())
            ("o, outputfile", "Write the index to the specified file",
                    cxxopts::value<std::string>())
            ("k, order", "The order of the tree",
                    cxxopts::value<int>()->default_value("3"))
            ("h, help", "Print help")

            ;
    options.parse_positional({"inputfile"});
    options.positional_help("inputfile");

    return options;
}


void Index::execute(const cxxopts::ParseResult& args) {
    std::cout << "Indexing file: " << args["inputfile"].as<std::string>() << std::endl;
    genogrove::IBPTree tree(args["order"].as<int>());
    genogrove::BEDfileValidator validator;

    std::string inputfile = args["inputfile"].as<std::string>();
    // detect the file type
    auto [filetype, gzipped] = genogrove::FileTypeDetector().detectFileType(inputfile);
    // validate the file
    std::string errorMessage;
    if(!genogrove::FileValidatorFactory::validate(inputfile, filetype, gzipped, errorMessage)) {
        std::cerr << "Error validating file: " << errorMessage << "\n";
        return;
    }

    std::cout << "Successfully validated file\n";






//    if(!validator.validate(inputfile)) {
//        std::cerr << validator.getErrorMessage() << std::endl;
//        return;
//    }
//
//







    if(args.count("inputfile")) {
        std::string inputfile = args["inputfile"].as<std::string>();
        std::cout << "Indexing file: " << inputfile << std::endl;
    }

    if(args.count("outputfile")) {
        std::string outputfile = args["outputfile"].as<std::string>();
        std::cout << "Writing index to file: " << outputfile << std::endl;
    }
}
