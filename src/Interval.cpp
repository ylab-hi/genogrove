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

    bool Interval::operator<=(const Interval& other) const {
        if(this->getStart() == other.getStart()) {
            return this->getEnd() <= other.getEnd(); // if start is equal, then check end
        } else {
            return this->getStart() <= other.getStart();
        }
    }

    bool Interval::operator>=(const Interval& other) const {
        if(this->getStart() == other.getStart()) {
            return this->getEnd() >= other.getEnd(); // if start is equal, then check end
        }
    }

    // getter & setter
    size_t Interval::getStart() const { return this->start; }
    void Interval::setStart(size_t start) { this->start = start; }
    size_t Interval::getEnd() const { return this->end; }
    void Interval::setEnd(size_t end) { this->end = end; }

    /*
     * @brief check if the parameter interval is left of the current interval
     * @param other the interval to check
     * @return true if the parameter interval is left of the current interval
     */
    bool Interval::leftOf(const Interval& other) const {
        return other.end < this->start;
    }
    bool Interval::overlap(const Interval& intvl1, const Interval& intvl2) {
        Interval intvl = {std::max(intvl1.getStart(), intvl2.getStart()),
                          std::min(intvl1.getEnd(), intvl2.getEnd())};
        return intvl.getStart() <= intvl.getEnd();
    }

    void Interval::serialize(std::ostream& os) const {
        os.write(reinterpret_cast<const char*>(&this->start), sizeof(this->start));
        os.write(reinterpret_cast<const char*>(&this->end), sizeof(this->end));
    }

    Interval Interval::deserialize(std::istream& is) {
        Interval intvl;
        is.read(reinterpret_cast<char*>(&intvl.start), sizeof(intvl.start));
        is.read(reinterpret_cast<char*>(&intvl.end), sizeof(intvl.end));
        return intvl;
    }

} // namespace

