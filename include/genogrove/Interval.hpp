#ifndef GENGROVE_INTERVAL_HPP
#define GENGROVE_INTERVAL_HPP

// Standard
#include <cstddef>
#include <string>
#include <iostream>
#include <compare>

namespace genogrove {
    class Interval {
        public:
            Interval();
            Interval(size_t start, size_t end);
            ~Interval();

            /*
             * @brief operator overloading that compares are non-overlapping (left-most end < right-most start)
             */
            std::strong_ordering operator<=>(const Interval& other) const;
            /*
            bool operator<(const Interval& other) const;
            bool operator>(const Interval& other) const;
            bool operator<=(const Interval& other) const;
            bool operator>=(const Interval& other) const;*/

            std::string toString() const;


            /*
             * @brief check if provided interval is left of class interval (no overlaps)
             */
            bool leftOf(const Interval& other) const;
            static bool overlap(const Interval& intvl1, const Interval& intvl2);

            // getter & setter
            size_t getStart() const;
            void setStart(size_t start);
            size_t getEnd() const;
            void setEnd(size_t end);

            void serialize(std::ostream& os) const;
            static Interval deserialize(std::istream& is);

        private:
            size_t start;
            size_t end;
        };

}


#endif //GENGROVE_INTERVAL_HPP
