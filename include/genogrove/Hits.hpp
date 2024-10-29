#ifndef GENOGROVE_HITS_HPP
#define GENOGROVE_HITS_HPP

// Standard
#include <vector>

// Class
#include "Interval.hpp"


namespace genogrove {
    using GenoInterval = std::pair<std::string, Interval>;

    class Hit {
        public:

        private:
            Interval query;

    };

    class Hits {
    public:
        Hit(std::string chromosome, genogrove::Interval interval, Key key);

    private:
        std::pair<std::string, Interval> query;
        std::vector<




        std::string chromosome;
        Interval query;
        std::vector<shared_ptr<AnyBase>>



        std::string chromosome;
        Interval interval;
        std::vector<std::pair<Interval, Key>>


    };
}


#endif //GENOGROVE_HITS_HPP
