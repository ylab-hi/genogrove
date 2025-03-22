#ifndef GENOGROVE_INTERSECT_HPP
#define GENOGROVE_INTERSECT_HPP

// Standard
#include <iostream>

// Class
#include "Subcall.hpp"

// CXXopts
#include "cxxopts.hpp"

class Intersect : public Subcall {
    public:
        cxxopts::Options parseArgs(int argc, char** argv) override;
        void execute(const cxxopts::ParseResult& args) override;

        // getter & setter
        cxxopts::Options getOptions();
        void setOptions(cxxopts::Options options);

};

#endif //GENOGROVE_INTERSECT_HPP
