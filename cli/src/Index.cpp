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
            ("s, sorted", "Interval in the input file are sorted",
                    cxxopts::value<bool>()->default_value("false"))
            ("t, timed", "Measure the time taken for indexing",
                    cxxopts::value<bool>()->default_value("false"))
            ("h, help", "Print help")
            ;
    options.parse_positional({"inputfile"});
    options.positional_help("inputfile");

    return options;
}


void Index::execute(const cxxopts::ParseResult& args) {
    auto startProgram = std::chrono::steady_clock::now();



    std::cout << "Indexing file: " << args["inputfile"].as<std::string>() << std::endl;

    std::filesystem::path inputfile = std::filesystem::path(args["inputfile"].as<std::string>());
    auto [filetype, gzipped] = FileTypeDetector().detectFileType(inputfile); // detect the file type
    // create the reader (according to the file type) - FileReaderFactory
    std::unique_ptr<FileReader> reader = FileReaderFactory::create(inputfile, filetype, gzipped);

    ggs::Grove tree(args["order"].as<int>()); // create the tree (with the specified order)
    FileEntry entry;

    // stop the time
    auto startInsertion = std::chrono::steady_clock::now();

    while(reader->hasNext()) {
//        std::cout << "Reading entry: " << reader->getCurrentLine() << std::endl;
        if(!reader->readNext(entry)) {
            if(reader->getErrorMessage().empty()) {
                break; // this is just an EOF
            }
            std::cerr << reader->getErrorMessage() << std::endl;
            return;
        }
        tree.insertData(entry.chrom, entry.interval, entry.strand);
    }

    std::cout << "Finished inserting data into the tree" << std::endl;
    auto endInsertion = std::chrono::steady_clock::now();
    std::chrono::duration<double> insertionDuration = endInsertion - startInsertion;
    std::cout << "Time taken for insertion: " << insertionDuration.count() << " seconds\n";


    // write the tree to a file
    std::filesystem::path outputfile;
    if(args.count("outputfile")) { // check if an output file was specified
        outputfile = std::filesystem::path(args["outputfile"].as<std::string>());
    } else { // if not, write to inputfile.gg (with a .gg extension)
        outputfile = inputfile.replace_extension(".gg");
        std::cout << "Writing index to file: " << outputfile << std::endl;
    }

    // serialize the tree
    tree.store(outputfile);

    // whole program time
    auto endProgram = std::chrono::steady_clock::now();
    std::chrono::duration<double> programDuration = endProgram - startProgram;
    std::cout << "Time taken for whole program: " << programDuration.count() << " seconds\n";


}
