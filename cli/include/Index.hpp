#ifndef GENOGROVE_INDEX_HPP
#define GENOGROVE_INDEX_HPP

// Class
#include "genogrove/all.hpp"
#include "Subcall.hpp"

// CXXopts
#include "cxxopts.hpp"

class Index : public Subcall {
    public:
        cxxopts::ParseResult parseArgs(int argc, char** argv) override;
        void execute(const cxxopts::ParseResult& args) override;
};

#endif //GENOGROVE_INDEX_HPP
