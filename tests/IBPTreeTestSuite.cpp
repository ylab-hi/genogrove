#include <gtest/gtest.h>
#include "genogrove/IBPTree.hpp"

#include <stdlib.h>

TEST(IBPTreeTestSuite, CreateIBPTree) {
    std::srand(std::time(nullptr));
    int k = 3;
    genogrove::IBPTree tree(k);
    std::vector<std::pair<genogrove::Interval, int>> intervals;

    // register types with the TypeRegistry
    genogrove::TypeRegistry::registerType<int>();

    intervals.push_back({{0, 10}, rand() % 100});
    for(size_t i=11; i < 10000000; i+=10) {
        intervals.push_back({{i, i+9}, rand() % 100});
    }
    auto startInsertion = std::chrono::steady_clock::now();
    std::cout << "#### Inserting data into the tree ####\n";
    for(auto& intvl : intervals) {
        genogrove::Key key{intvl.first, intvl.second};
        std::cout << "Inserting key: " << key.getInterval().getStart() << "," << key.getInterval().getEnd();
        std::cout << " with the data: " << intvl.second << "\n";
        tree.insert("chr1", key);
    }
    auto endInsertion = std::chrono::steady_clock::now();
    std::chrono::duration<double> insertionDuration = endInsertion - startInsertion;
    std::cout << "Time taken for insertion: " << insertionDuration.count() << " seconds\n\n";
    std::cout << "#### Searching for data within the tree ####\n";
    auto startSearch = std::chrono::steady_clock::now();
    for(auto& intvl : intervals) {
        std::cout << "Searching for interval [" << intvl.first.getStart() << "," << intvl.first.getEnd() << "]";
        std::cout << " with the data: " << intvl.second << "\n";
        auto searchResult = tree.search("chr1", intvl.first);
        EXPECT_EQ(searchResult.size(), 1) << "The search result for interval [" << intvl.first.getStart()
                                          << "," << intvl.first.getEnd() << "] was not correct (count mismatch)";
        EXPECT_EQ(std::any_cast<int>(searchResult[0]), intvl.second) << "The search result for interval ["
            << intvl.first.getStart() << "," << intvl.first.getEnd() << "] was not correct (data mismatch)";
    }
    auto endSearch = std::chrono::steady_clock::now();
    std::chrono::duration<double> searchDuration = endSearch - startSearch;
    std::cout << "Time taken for search: " << searchDuration.count() << " seconds\n\n";
}