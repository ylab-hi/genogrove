#ifndef GENOGROVE_CHROMS_HPP
#define GENOGROVE_CHROMS_HPP

// Standard
#include <bitset>
#include <unordered_map>
#include <stdexcept>

namespace genogrove {
    static constexpr size_t BITS = 6; // 2^6 = 64 chromosomes (should be enough for now...)

    class Chroms {
    public:
        Chroms();

        //
        std::bitset<BITS> registerChrom(const std::string& chrom);
        std::bitset<BITS> getNextBitset() const;
        std::bitset<BITS> getBitset(std::string chrom) const;

    private:
        std::unordered_map<std::string, std::bitset<BITS>> chromosomes;
        size_t nextValue;
    };
}


#endif //GENOGROVE_CHROMS_HPP
