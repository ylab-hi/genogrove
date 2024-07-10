#include <gtest/gtest.h>
#include "IBPTree.hpp"

#include <stdlib.h>

TEST(IBPTreeTestSuite, CreateIBPTree) {
    int k = 3;
    IBPTree tree(k);
    std::vector<dtp::Interval> intervals = {{0, 10}, {10, 20}, {20, 30}, {30, 40}, {40, 50},
                                            {50, 60}, {60, 70}, {70, 80}, {80, 90}, {90, 100}};
    for(dtp::Interval interval : intervals) {
        // random number
        int data = rand() % 100;
        std::shared_ptr<void> dataPtr = std::make_shared<int>(data);
        tree.insert("chr1", interval, dataPtr);
    }
}