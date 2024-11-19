#ifndef GENOGROVE_FILEREADER_HPP
#define GENOGROVE_FILEREADER_HPP

// Class
#include "genogrove/Interval.hpp"
#include "FileEntry.hpp"

class FileReader {
    public:
        virtual bool readNext(FileEntry& entry) = 0;
        virtual bool hasNext() = 0;
        virtual std::string getErrorMessage() = 0;
        virtual size_t getCurrentLine() = 0;
        virtual ~FileReader() = default;
};

#endif //GENOGROVE_FILEREADER_HPP
