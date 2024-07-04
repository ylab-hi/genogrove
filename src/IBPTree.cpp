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
        newRoot->addChild(root);
        splitNode(newRoot, 0);
        root = newRoot;
        this->rootnodes[key] = root;

    }
}

void IBPTree::splitNode(Node* parent, int index) {
    // std::cout << "Splitting node " << parent->keysToString() << " at index " << index << "\n";
    Node* child = parent->getChild(index);
    Node* newChild = new Node(this->order);
    int mid = ((this->order+2-1)/2); // value for order=6

    newChild->setIsLeaf(child->getIsLeaf());
    newChild->keys.assign(child->keys.begin() + mid, child->keys.end());
    child->keys.resize(this->order-1);

    // update parent
    parent->children.insert(parent->children.begin() + index + 1, newChild);
    parent->keys.insert(parent->keys.begin() + index, {child->calcNewKey(), nullptr});

    if(child->isLeaf) {
        newChild->next = child->next;
        child->next = newChild;
    } else {
        newChild->children.assign(child->children.begin() + mid, child->children.end());
        child->children.resize(mid + 1);
    }
}






