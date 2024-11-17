#ifndef GENOGROVE_FILEVALIDATOR_HPP
#define GENOGROVE_FILEVALIDATOR_HPP

// Standard
#include <filesystem>

// Class
#include "FileFormatValidator.hpp"
#include "FileTypeDetector.hpp"
#include "BEDfileValidator.hpp"

namespace genogrove {
    class FileValidatorFactory {
        public:
            static bool validate(const std::filesystem::path& filepath,
                                 FileType filetype,
                                 std::bitset<1> gzipped,
                                 std::string& errorMessage) {
                std::unique_ptr<FileFormatValidator> validator;
                switch(filetype) {
                    case FileType::BED:
                        validator = std::make_unique<BEDfileValidator>();
                        break;
                    default:
                        errorMessage = "Unsupported file type";
                        return false;
                }
                return true;
            }
    };
}

#endif //GENOGROVE_FILEVALIDATOR_HPP
