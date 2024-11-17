#include "BEDfileValidator.hpp"

namespace genogrove {
    BEDfileValidator::BEDfileValidator() : errorMessage("") {}

    bool BEDfileValidator::validate(std::string& filepath) {
        std::ifstream infile(filepath);
        if(!infile.is_open()) {
            errorMessage = "Failed to open file: " + filepath;
            return false;
        }

        std::string line;
        int lineNum = 1;
        while(std::getline(infile, line)) {
            if(!isValidLine(line, lineNum)) {
                return false;
            }
            lineNum++;
        }
        return true;
    }

    std::string BEDfileValidator::getErrorMessage() {
        return errorMessage;
    }

    bool BEDfileValidator::isValidLine(std::string& line, int lineNum) {
        std::stringstream ss(line);
        std::string chrom, start, end;

        if(!(ss >> chrom >> start >> end)) { // check if first three columns are valid
            errorMessage = "Invalid line in file (line " + std::to_string(lineNum) + "): " + line;
            return false;
        }

        if(!isValidInteger(start) || !isValidInteger(end)) { // check if start and end are valid integers
            errorMessage = "Invalid start or end coordinate in file (line " + std::to_string(lineNum) + "): " + line;
            return false;
        }

        if(std::stoi(start) >= std::stoi(end)) { // check if start is less than or equal to end
            errorMessage = "Start coordinate is greater than end coordinate in file (line " + std::to_string(lineNum) + "): " + line;
            return false;
        }
        return true;
    }

    bool BEDfileValidator::isValidInteger(std::string& str) {
        return std::all_of(str.begin(), str.end(), ::isdigit);
    }
}


