#ifndef GENOGROVE_FILEREADERFACTORY_HPP
#define GENOGROVE_FILEREADERFACTORY_HPP

// Standard
#include <filesystem>

// Class
#include "FileReader.hpp"
#include "BEDReader.hpp"
#include "FileTypeDetector.hpp"

class FileReaderFactory {
    public:
        static std::unique_ptr<FileReader> create(
                const std::filesystem::path& filepath,
                FileType filetype,
                bool gzipped
                ) {
            switch(filetype) {
                case FileType::BED:
                    return std::make_unique<BEDReader>(filepath, gzipped);
                default:
                    return nullptr;
            }
        }
};

#endif //GENOGROVE_FILEREADERFACTORY_HPP
