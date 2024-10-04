#include <gtest/gtest.h>
#include "genogrove/IBPTree.hpp"

TEST(SerializationTestSuite, StoreTree) {
    int k = 20;
    genogrove::IBPTree tree(k);

    std::vector<std::pair<genogrove::Interval, int>> intervals;
    intervals.push_back({{0, 10}, rand() % 100});
    for(size_t i=11; i < 10000000; i+=10) {
        intervals.push_back({{i, i+9}, rand() % 100});
    }

    // register types with the TypeRegistry
    genogrove::TypeRegistry::registerType<int>();

    for(auto& intvl : intervals) {
        tree.insertData("chr1", intvl.first, intvl.second);
    }
    std::cout << "Building tree" << std::endl;
    tree.store("test.gg");
}