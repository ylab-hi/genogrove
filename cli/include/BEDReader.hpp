#ifndef GENOGROVE_BEDREADER_HPP
#define GENOGROVE_BEDREADER_HPP

// Standard
#include <string>
#include <filesystem>
#include <istream>
#include <algorithm>

// Class
#include "FileReader.hpp"
#include "genogrove/Interval.hpp"
#include "FileEntry.hpp"

class BEDReader : public FileReader {
    public:
        BEDReader(const std::filesystem::path&, bool gzipped);
        bool readNext(FileEntry& entry) override;
        bool hasNext() override;
        std::string getErrorMessage() override;

    private:
        std::unique_ptr<std::istream> inputStream;
        std::string errorMessage;
        size_t lineNum;
};

#endif //GENOGROVE_BEDREADER_HPP
