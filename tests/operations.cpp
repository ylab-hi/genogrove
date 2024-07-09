#include <gtest/gtest.h>
#include "IBPTree.hpp"

TEST(IBPTreeConstruction, construct) {
    int k = 3;
    IBPTree<int> tree(k);
    std::vector<dtp::Interval> intervals = {{0, 10}, {10, 20}, {20, 30}, {30, 40}, {40, 50},
                                            {50, 60}, {60, 70}, {70, 80}, {80, 90}, {90, 100}};

    for(dtp::Interval interval : intervals) {
        int data = 32;
        tree.insert("chr1", interval, data);
    }
}