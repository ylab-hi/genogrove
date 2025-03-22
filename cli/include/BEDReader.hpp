#ifndef GENOGROVE_BEDREADER_HPP
#define GENOGROVE_BEDREADER_HPP

// Standard
#include <string>
#include <filesystem>
#include <istream>
#include <fstream>
#include <algorithm>

// Class
#include "FileReader.hpp"
#include "genogrove/Interval.hpp"
#include "FileEntry.hpp"

// zlib
#include <zlib.h>
#include <sstream>

#include <htslib/hts.h>
#include <htslib/bgzf.h>
#include <htslib/kseq.h>
#include <htslib/kstring.h>

namespace ggt = genogrove::type;

class BEDReader : public FileReader {
    public:
        BEDReader(const std::filesystem::path&, bool gzipped);
        bool readNext(FileEntry& entry) override;
        bool hasNext() override;
        std::string getErrorMessage() override;
        size_t getCurrentLine() override;
        ~BEDReader();

    private:
        BGZF* bgzfFile;
        size_t lineNum;
        std::string errorMessage;
//        std::unique_ptr<std::ifstream> inputStream;
//        size_t lineNum;
};

#endif //GENOGROVE_BEDREADER_HPP
