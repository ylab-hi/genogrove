#include "genogrove/Chroms.hpp"

namespace genogrove {
    Chroms::Chroms() : chromosomes{}, nextValue{0} {}

    std::bitset<constants::BITS> Chroms::registerChrom(const std::string& chrom) {
        auto it = chromosomes.find(chrom);
        if(it != chromosomes.end()) {
            return it->second; // chromosome is already registered
        }

        // create a new bitset (for the provided chromosome)
        std::bitset<constants::BITS> bits(nextValue);
        chromosomes[chrom] = bits;
        nextValue++;
        return bits;
    }

    // get the next available bitset (without registering the chromosome)
    std::bitset<constants::BITS> Chroms::getNextBitset() const {
        return std::bitset<constants::BITS>(nextValue);
    }

    std::bitset<constants::BITS> Chroms::getBitset(std::string chrom) const {
        auto it = chromosomes.find(chrom);
        if(it != chromosomes.end()) {
            throw std::runtime_error("Chromosome " + chrom + " not registered");
        }
        return it->second;
    }
}
