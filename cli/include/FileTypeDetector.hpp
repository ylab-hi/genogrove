#ifndef GENOGROVE_FILETYPEDETECTOR_HPP
#define GENOGROVE_FILETYPEDETECTOR_HPP

// Standard
#include <string>
#include <fstream>
#include <iostream>
#include <bitset>
#include <unordered_map>
#include <filesystem>

namespace genogrove {
    enum class FileType {
        BED,
        BEDGRAPH,
        GFF,
        GTF,
        VCF,
        UNKNOWN
    };

    class FileTypeDetector {
        public:
            std::tuple<FileType, bool> detectFileType(const std::filesystem::path& filepath);
    };
}


#endif //GENOGROVE_FILETYPEDETECTOR_HPP
