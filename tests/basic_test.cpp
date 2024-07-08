#include <gtest/gtest.h>
#include "IBPTree.hpp"

TEST(IBPTree, Constructor) {
    for(int k=3; k < 10; k++) {
        IBPTree tree(k);
        EXPECT_EQ(tree.getOrder(), k) << "The order k=" + std::to_string(k) + " was not set correctly";
    }
}

TEST(IBPTree, GetRoot) {
    IBPTree tree(3);
    EXPECT_EQ(tree.getRootnodes().size(), 0) << "The rootnodes map was not empty";
    tree.getRoot("test");
    ASSERT_EQ(tree.getRoot("test"), nullptr) << "The newly create root node for key \"test\" should be nullptr";
}
