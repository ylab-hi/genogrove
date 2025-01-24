#ifndef GENOGROVE_CHROMS_HPP
#define GENOGROVE_CHROMS_HPP

// Standard
#include <bitset>
#include <unordered_map>
#include <stdexcept>

// Class
#include "Constants.hpp"

namespace genogrove {

    class Chroms {
    public:
        Chroms();

        //
        std::bitset<constants::BITS> registerChrom(const std::string& chrom);
        std::bitset<constants::BITS> getNextBitset() const;
        std::bitset<constants::BITS> getBitset(std::string chrom) const;

    private:
        std::unordered_map<std::string, std::bitset<constants::BITS>> chromosomes;
        size_t nextValue;
    };
}


#endif //GENOGROVE_CHROMS_HPP
