#include "genogrove/Interval.hpp"

namespace genogrove {
    Interval::Interval() : start(std::string::npos), end(std::string::npos) {}
    Interval::Interval(size_t start, size_t end) : start(start), end(end) {}
    Interval::~Interval() {}

    bool Interval::operator<(const Interval& other) const {
        if(this->getStart() == other.getStart()) {
            return this->getEnd() < other.getEnd(); // if start is equal, then check end
        } else {
            return this->getStart() < other.getStart();
        }
    }

    bool Interval::operator>(const Interval& other) const {
        if(this->getStart() == other.getStart()) {
            return this->getEnd() > other.getEnd(); // if start is equal, then check end
        } else {
            return this->getStart() > other.getStart();
        }
    }

    // getter & setter
    size_t Interval::getStart() const { return this->start; }
    void Interval::setStart(size_t start) { this->start = start; }
    size_t Interval::getEnd() const { return this->end; }
    void Interval::setEnd(size_t end) { this->end = end; }

    bool Interval::overlap(const Interval& other) const {
        return std::max(this->start, other.start) - std::min(this->end, other.end) <= 0;
    }

    /*
     * @brief check if the parameter interval is left of the current interval
     * @param other the interval to check
     * @return true if the parameter interval is left of the current interval
     */
    bool Interval::leftOf(const Interval& other) const {
        return other.end < this->start;
    }
} // namespace
