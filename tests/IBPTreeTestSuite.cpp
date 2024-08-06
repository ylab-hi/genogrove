#include <gtest/gtest.h>
#include "IBPTree.hpp"

#include <stdlib.h>

TEST(IBPTreeTestSuite, CreateIBPTree) {
    std::srand(std::time(nullptr));
    int k = 3;
    IBPTree tree(k);
    std::vector<std::pair<Interval, std::shared_ptr<void>>> intervals;

    intervals.push_back({{0, 10}, std::make_shared<int>(rand() % 100)});
    for(int i=11; i < 10000; i+=10) {
        intervals.push_back({{static_cast<size_t>(i), static_cast<size_t>(i+9)},
                             std::make_shared<int>(rand() % 100)});
    }

    std::cout << "#### Inserting data into the tree ####\n";

    // insert data into the tree
    std::vector<std::shared_ptr<void>> dataVector;
    for(auto& intvl : intervals) { // insert data
        Key key{intvl.first, intvl.second};
        std::cout << "Inserting key: " << key.getInterval().getStart() << "," << key.getInterval().getEnd();
        std::cout << " with the data: " << *std::static_pointer_cast<int>(intvl.second) << "\n";
        tree.insert("chr1", key);
    }

    std::cout << "#### Searching for data within the tree ####\n";

    // search for data within the tree
    for(auto& intvl : intervals) {
        std::cout << "Searching for interval [" << intvl.first.getStart() << "," << intvl.first.getEnd() << "]";
        std::cout << " with the data: " << *std::static_pointer_cast<int>(intvl.second);
        std::vector<std::shared_ptr<void>> searchResult = tree.search("chr1", intvl.first);

        std::cout << " -> search result: ";
        for(auto& data : searchResult) {
            std::cout << *std::static_pointer_cast<int>(data) << " ";
        }
        std::cout << "\n";
        EXPECT_EQ(searchResult.size(), 1) << "The search result for interval [" << intvl.first.getStart() << ","
                                          << intvl.first.getEnd() << "] was not correct";
        EXPECT_EQ(*std::static_pointer_cast<int>(searchResult[0]), *std::static_pointer_cast<int>(intvl.second))
            << "The search result for interval [" << intvl.first.getStart() << "," << intvl.first.getEnd() << "] was not correct";
    }
}