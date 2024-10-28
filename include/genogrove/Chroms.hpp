#ifndef GENOGROVE_CHROMS_HPP
#define GENOGROVE_CHROMS_HPP

// Standard
#include <bitset>
#include <unordered_map>

class Chroms {
    public:
        Chroms();

    private:
        static constexpr size_t BITS = 6; // 2^6 = 64 chromosomes (should be enough for now...)
        std::unordered_map<std::string, std::bitset<BITS>> chromsMap;
};

#endif //GENOGROVE_CHROMS_HPP
