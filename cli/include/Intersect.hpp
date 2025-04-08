#ifndef GENOGROVE_INTERSECT_HPP
#define GENOGROVE_INTERSECT_HPP

// Standard
#include <iostream>

// Class
#include "Subcall.hpp"
#import "genogrove/all.hpp"
#import "FileReaderFactory.hpp"
#import "FileTypeDetector.hpp"



// CXXopts
#include "cxxopts.hpp"

namespace ggt = genogrove::type;
namespace ggs = genogrove::structure;

class Intersect : public Subcall {
    public:
        cxxopts::Options parseArgs(int argc, char** argv) override;
        void execute(const cxxopts::ParseResult& args) override;
        void validate(const cxxopts::ParseResult& args) override;

        // getter & setter
        cxxopts::Options getOptions();
        void setOptions(cxxopts::Options options);

};

#endif //GENOGROVE_INTERSECT_HPP
