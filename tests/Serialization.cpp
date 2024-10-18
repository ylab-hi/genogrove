#include <gtest/gtest.h>
#include "genogrove/IBPTree.hpp"

TEST(SerializationTestSuite, StoreAndLoadTree) {
    int k = 3;
    genogrove::IBPTree tree(k);

    std::vector<std::pair<genogrove::Interval, int>> intervals;
    intervals.push_back({{0, 10}, rand() % 100});
    for (size_t i = 11; i < 1000; i += 10) {
        intervals.push_back({{i, i + 9}, rand() % 100});
    }

    // register types with the TypeRegistry
    genogrove::TypeRegistry::registerType<int>();

    for (auto &intvl: intervals) {
        tree.insertData("chr1", intvl.first, intvl.second);
    }
    std::cout << "Building tree" << std::endl;
    std::cout << "####### Storing tree ######" << std::endl;
    tree.store("/output/test.gg");

    genogrove::TypeRegistry::instance().reset(); // reset the TypeRegistry (for testing)

    std::cout << "Loading tree" << std::endl;
    genogrove::TypeRegistry::registerType<int>(); // register the int type for testing
    genogrove::IBPTree tree2 = genogrove::IBPTree::load("/output/test.gg");

    for (auto &intvl: intervals) {
        auto searchResult = tree2.overlaps("chr1", intvl.first);
        EXPECT_EQ(searchResult.size(), 1) << "The search result for interval [" << intvl.first.getStart()
                                          << "," << intvl.first.getEnd() << "] was not correct (count mismatch)";
    }
}

