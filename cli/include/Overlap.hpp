#ifndef GENOGROVE_OVERLAP_HPP
#define GENOGROVE_OVERLAP_HPP

// Standard
#include <iostream>

// Class
#include "Subcall.hpp"

// CXXopts
#include "cxxopts.hpp"

class Overlap : public Subcall {
    public:
        cxxopts::ParseResult parseArgs(int argc, char** argv) override;
        void execute(const cxxopts::ParseResult& args) override;
};

#endif //GENOGROVE_OVERLAP_HPP
