#include "Utility.hpp"

std::string cli::getTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // convert the time and date to a string in the format "YYYY-MM-DD"
    std::stringstream timeStream;
    timeStream << std::put_time(std::localtime(&currentTime), "[%Y-%m-%d %H:%M:%S]") << " ";
    std::string timeString = timeStream.str();

    return timeString;
}


