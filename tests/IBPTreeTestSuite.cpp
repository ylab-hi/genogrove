#include <gtest/gtest.h>
#include "IBPTree.hpp"

#include <stdlib.h>

TEST(IBPTreeTestSuite, CreateIBPTree) {
    std::srand(std::time(nullptr));
    int k = 3;
    IBPTree tree(k);
    std::vector<std::pair<dtp::Interval, std::shared_ptr<void>>> intervals;
    intervals.push_back({{0, 10}, std::make_shared<int>(rand() % 100)});
    intervals.push_back({{11, 20}, std::make_shared<int>(rand() % 100)});
    intervals.push_back({{21, 30}, std::make_shared<int>(rand() % 100)});
    intervals.push_back({{31, 40}, std::make_shared<int>(rand() % 100)});
    intervals.push_back({{41, 50}, std::make_shared<int>(rand() % 100)});
    intervals.push_back({{51, 60}, std::make_shared<int>(rand() % 100)});
    intervals.push_back({{61, 70}, std::make_shared<int>(rand() % 100)});
    intervals.push_back({{71, 80}, std::make_shared<int>(rand() % 100)});
    intervals.push_back({{81, 90}, std::make_shared<int>(rand() % 100)});
    intervals.push_back({{91, 100}, std::make_shared<int>(rand() % 100)});


/*
*/
    // insert data into the tree
    std::vector<std::shared_ptr<void>> dataVector;
    for(auto& intvl : intervals) { // insert data
        KeyPtr key = std::make_shared<Key>(intvl.first, intvl.second);
        std::cout << "Inserting key: " << key->getInterval().first << "," << key->getInterval().second;
        std::cout << " with the data: " << *std::static_pointer_cast<int>(intvl.second) << "\n";
        tree.insert("chr1", key);
    }

    // search for data within the tree
    for(auto& intvl : intervals) {
        std::cout << "Searching for interval [" << intvl.first.first << "," << intvl.first.second << "]";
        std::cout << " with the data: " << *std::static_pointer_cast<int>(intvl.second);
        std::vector<std::shared_ptr<void>> searchResult = tree.search("chr1", intvl.first);

        std::cout << " -> search result: ";
        for(auto& data : searchResult) {
            std::cout << *std::static_pointer_cast<int>(data) << " ";
        }
        std::cout << "\n";
        EXPECT_EQ(searchResult.size(), 1) << "The search result for interval [" << intvl.first.first << ","
                                          << intvl.first.second << "] was not correct";
        EXPECT_EQ(*std::static_pointer_cast<int>(searchResult[0]), *std::static_pointer_cast<int>(intvl.second))
            << "The search result for interval [" << intvl.first.first << "," << intvl.first.second << "] was not correct";
    }
}