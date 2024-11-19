#include "BEDReader.hpp"


BEDReader::BEDReader(const std::filesystem::path& filepath, bool gzipped) {
    lineNum = 1;
    if(gzipped) {
        // open file gzipped
    } else {
        inputStream = std::make_unique<std::ifstream>(filepath);
        if(!inputStream->is_open()) {
            throw std::runtime_error("Failed to open file: " + filepath.string());
        }
    }
}

bool BEDReader::readNext(FileEntry& entry) {
    std::string line;
    if(!std::getline(*inputStream, line)) {
        errorMessage = "Failed to read line at line " + std::to_string(lineNum);
    }

    std::stringstream ss(line);
    std::string chrom, start, end;

    try {
        if(!(ss >> chrom >> start >> end)) {
            errorMessage = "Invalid line format at line " + std::to_string(lineNum);
            return false;
        }

        // validate integers
        if(!std::all_of(start.begin(), start.end(), ::isdigit) ||
            !std::all_of(end.begin(), end.end(), ::isdigit)) {
            errorMessage = "Invalid coordinate format at line " + std::to_string(lineNum);
            return false;
        }

        // validate and create interval object
        size_t startNum = std::stoul(start);
        size_t endNum = std::stoul(end);
        if(startNum >= endNum) {
            errorMessage = "Start coordinate must be less than end coordinate at line " + std::to_string(lineNum);
            return false;
        }

        // modify the passen entry
        entry.chrom = chrom;
        entry.interval = genogrove::Interval{startNum, endNum};
        entry.strand = '.';

        lineNum++;
        return true;

    } catch(std::exception& e) {
        errorMessage = "Failed to parse line at line " + std::to_string(lineNum) + ": " + line;
        return false;
    }
}

bool BEDReader::hasNext() {
    return inputStream && !inputStream->eof();
}

std::string BEDReader::getErrorMessage() {
    return errorMessage;
}

size_t BEDReader::getCurrentLine() {
    return lineNum;
}

