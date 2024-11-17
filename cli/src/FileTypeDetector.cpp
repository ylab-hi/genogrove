#include "FileTypeDetector.hpp"

namespace genogrove {

    static const std::unordered_map<std::string, FileType> extensions = {
            {".bed", FileType::BED},
            {".bedgraph", FileType::BEDGRAPH},
            {".gff", FileType::GFF},
            {".gtf", FileType::GTF},
            {".vcf", FileType::VCF}
    };

    std::tuple<FileType, std::bitset<1>> FileTypeDetector::detectFileType(const std::filesystem::path& filepath) {
        std::ifstream file(filepath, std::ios::binary);
        if(!file) { throw std::runtime_error("Failed to open file: " + filepath.string()); }

        // check if the file is gzipped
        char buffer[2];
        file.read(buffer, 2);
        std::bitset<1> gzipped(0);
        if(file.gcount() == 2 && buffer[0] == 0x1f && buffer[1] == 0x8b) { gzipped = std::bitset<1>(1); }

        // extract the file extension
        std::string extension = filepath.extension().string();
        if(gzipped == std::bitset<1>(1) && extension == ".gz") {
            extension = filepath.stem().extension().string();
        }

        // look up the file type
        auto it = extensions.find(extension);
        FileType filetype = (it != extensions.end()) ? it->second : FileType::UNKNOWN;

        return std::make_tuple(filetype, gzipped);
    }
}
