#ifndef IBPTREE_IBPTREE_HPP
#define IBPTREE_IBPTREE_HPP

// Standard
#include <map>

// Class
#include "Node.hpp"
#include "DataTypes.hpp"

class IBPTree {
    public:
        IBPTree(int k); // create a new IBPTree with a given order k
        ~IBPTree(); // destructor

        // operations on the tree
        Node* getRoot(std::string);
        template <typename T>
        void insert(T& data);
        template <typename T>
        void insertIter(Node* node, T& data);

    private:
        std::map<std::string, Node*> rootnodes; // root nodes of the IBPTree
        int order; // order of the IBPTree

};

#endif //IBPTREE_IBPTREE_HPP
