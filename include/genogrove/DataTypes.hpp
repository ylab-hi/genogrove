#ifndef IBPTREE_DATATYPES_HPP
#define IBPTREE_DATATYPES_HPP

// Class
#include "Interval.hpp"
#include "AnyType.hpp"

namespace genogrove {
    namespace dtp {
        // genomic coordinates
        struct Coordinate {
            std::string chromosome;
            char strand;
            Interval interval;

            Coordinate(std::string chromosome, char strand, Interval interval) :
                chromosome(chromosome), strand(strand), interval(interval) {}
        };

        struct Hit {
            Coordinate coordinate;
            std::shared_ptr<AnyBase> data;

            Hit(Coordinate coordinate, std::shared_ptr<AnyBase> data) :
                coordinate(coordinate), data(data) {}
        };

        struct Hits {
            Coordinate query;
            std::vector<Hit> hits;

            Hits(Coordinate query) : query(query), hits(std::vector<Hit>()) {}
            void addHit(Hit hit) { hits.push_back(hit); }
        };
    }
}


#endif //IBPTREE_DATATYPES_HPP
