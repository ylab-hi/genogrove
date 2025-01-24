#include "BEDReader.hpp"

BEDReader::BEDReader(const std::filesystem::path& filepath, bool gzipped) {
    bgzfFile = bgzf_open(filepath.c_str(), "r"); // open file
    if(!bgzfFile) {
        throw std::runtime_error("Failed to open file: " + filepath.string());
    }
}

BEDReader::~BEDReader() {
    if(bgzfFile) {
        bgzf_close(bgzfFile);
    }
}

bool BEDReader::readNext(FileEntry& entry) {
    kstring_t str = {0, 0, nullptr};
    int ret = bgzf_getline(bgzfFile, '\n', &str);
    if(ret < 0) {
        if(str.s) free(str.s);
        return false;
    }
    std::string line(str.s);
    free(str.s); // free the memory allocated by bgzf_getline

    // skip empty or commented lines
    if (line.empty() || line[0] == '#') {
        lineNum++;
        return readNext(entry);
    }

    // parse the line
    std::stringstream ss(line);
    std::string chrom, start, end;
    try {
        if (!(ss >> chrom >> start >> end)) {
            errorMessage = "Invalid line format at line " + std::to_string(lineNum);
            return false;
        }

        // validate integers
        if (!std::all_of(start.begin(), start.end(), ::isdigit) ||
            !std::all_of(end.begin(), end.end(), ::isdigit)) {
            errorMessage = "Invalid coordinate format at line " + std::to_string(lineNum);
            return false;
        }

        // validate and create interval object
        size_t startNum = std::stoul(start);
        size_t endNum = std::stoul(end);
        if (startNum >= endNum) {
            errorMessage = "Start coordinate is greater than end coordinate at line " + std::to_string(lineNum);
            return false;
        }
        entry.chrom = chrom;
        entry.interval = genogrove::Interval(startNum, endNum);
        entry.strand = '.';
        lineNum++;
        return true;
    } catch (std::exception &e) {
        errorMessage = "Failed to parse line at " + std::to_string(lineNum) + ": " + line;
        return false;
    }
}

bool BEDReader::hasNext() {
    return bgzfFile && !bgzf_check_EOF(bgzfFile);
}

std::string BEDReader::getErrorMessage() {
    return errorMessage;
}

size_t BEDReader::getCurrentLine() {
    return lineNum;
}

