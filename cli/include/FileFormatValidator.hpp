#ifndef GENOGROVE_FILEFORMATVALIDATOR_HPP
#define GENOGROVE_FILEFORMATVALIDATOR_HPP

#include <string>

namespace genogrove {
    class FileFormatValidator {
        public:
            virtual bool validate(std::string& filepath) = 0;
            virtual std::string getErrorMessage() = 0;
            virtual ~FileFormatValidator() = default;

    };
};

#endif //GENOGROVE_FILEFORMATVALIDATOR_HPP
