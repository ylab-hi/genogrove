#ifndef GENOGROVE_BEDFILEVALIDATOR_HPP
#define GENOGROVE_BEDFILEVALIDATOR_HPP

// Class
#include "FileFormatValidator.hpp"

// Standard
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>

namespace genogrove {
    class BEDfileValidator : public FileFormatValidator {
        public:
            BEDfileValidator();
            bool validate(std::string& filepath) override;
            std::string getErrorMessage() override;

            bool isValidLine(std::string& line, int lineNum);
            bool isValidInteger(std::string& str);

        private:
            std::string errorMessage;
    };
}

#endif //GENOGROVE_BEDFILEVALIDATOR_HPP
