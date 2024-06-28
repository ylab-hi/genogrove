#include "IBPTree.hpp"

IBPTree::IBPTree(int k) {
    this->order = k;
}


// operations on the tree

Node* IBPTree::getRoot(std::string key) {
    Node* root;
    if(this->rootnodes.find(key) == this->rootnodes.end()) {
        root = new Node(this->order);
        root->setIsLeaf(true); // root node becomes a leaf node
    } else {
        root = this->rootnodes[key];
    }
    return root;
}


template <typename T>
void IBPTree::insert(std::string key, T& data) {
    Node* root = getRoot(key);
    insertIter(root, data);
    if(root->getKeys().size() == this->order) {
        Node* newRoot = new Node(this->order);
        newRoot->children

    }


}






