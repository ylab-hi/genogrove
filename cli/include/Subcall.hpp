#ifndef GENOGROVE_SUBCALL_HPP
#define GENOGROVE_SUBCALL_HPP

#include "cxxopts.hpp"

class Subcall {
    public:
        virtual cxxopts::Options parseArgs(int argc, char** argv) = 0;
        virtual void execute(const cxxopts::ParseResult& args) = 0;
        virtual void validate(const cxxopts::ParseResult& args) = 0;
        virtual ~Subcall() = default;

};

#endif //GENOGROVE_SUBCALL_HPP
