#ifndef GENGROVE_INTERVAL_HPP
#define GENGROVE_INTERVAL_HPP

// Standard
#include <cstddef>
#include <string>

class Interval {
    public:
        Interval();
        Interval(size_t start, size_t end);
        ~Interval();

        /*
         * @brief operator overloading that compares are non-overlapping (left-most end < right-most start)
         */
        bool operator<(const Interval& other) const;
        bool operator>(const Interval& other) const;

        bool overlap(const Interval& other) const;
        /*
         * @brief check if provided interval is left of class interval (no overlaps)
         */
        bool leftOf(const Interval& other) const;

        // getter & setter
        size_t getStart() const;
        void setStart(size_t start);
        size_t getEnd() const;
        void setEnd(size_t end);

    private:
        size_t start;
        size_t end;
};

#endif //GENGROVE_INTERVAL_HPP
