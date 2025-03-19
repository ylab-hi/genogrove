#ifndef GENOGROVE_FILEENTRY_HPP
#define GENOGROVE_FILEENTRY_HPP

// Standard
#include <string>

// Class
#include "genogrove/Interval.hpp"

namespace ggt = genogrove::type;

struct FileEntry {
    std::string chrom;
    ggt::Interval interval;
    char strand;

    FileEntry() : chrom(""), interval(0, 0), strand('.') {}
    FileEntry(std::string chrom, ggt::Interval interval, char strand) :
        chrom(chrom), interval(interval), strand(strand) {}
};

#endif //GENOGROVE_FILEENTRY_HPP
