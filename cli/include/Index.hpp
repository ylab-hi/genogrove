#ifndef GENOGROVE_INDEX_HPP
#define GENOGROVE_INDEX_HPP

// Standard
#include <cstdlib>

// Class
#include "genogrove/all.hpp"
#include "Subcall.hpp"
#include "FileReader.hpp"
#include "BEDReader.hpp"
#include "FileEntry.hpp"
#include "FileTypeDetector.hpp"
#include "FileReaderFactory.hpp"

// CXXopts
#include "cxxopts.hpp"

namespace ggt = genogrove::type;
namespace ggs = genogrove::structure;

class Index : public Subcall {
    public:
        cxxopts::Options parseArgs(int argc, char** argv) override;
        void execute(const cxxopts::ParseResult& args) override;

};

#endif //GENOGROVE_INDEX_HPP