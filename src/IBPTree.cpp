#include "IBPTree.hpp"

IBPTree::IBPTree(int k) {
    this->order = k;
}


// operations on the tree

Node* IBPTree::getRoot(std::string key) {
    Node* root;
    if(this->rootnodes.find(key) == this->rootnodes.end()) {
        root = new Node(this->order);
        root->is



    }
}


template <typename T>
void IBPTree::insert(T t) {

}






