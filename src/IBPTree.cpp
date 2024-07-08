#include "IBPTree.hpp"

IBPTree::IBPTree(int k) : order(k), rootnodes{} {}
IBPTree::~IBPTree() {}

int IBPTree::getOrder() { return this->order; }
void IBPTree::setOrder(int k) { this->order = k; }
std::map<std::string, Node*> IBPTree::getRootnodes() { return this->rootnodes; }
void IBPTree::setRootnodes(std::map<std::string, Node*> rootnodes) { this->rootnodes = rootnodes; }

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
void IBPTree::insert(std::string key, dtp::Interval interval, T& data) {
    Node* root = getRoot(key);
    insertIter(root, data);
    if(root->getKeys().size() == this->order) {
        Node* newRoot = new Node(this->order);
        newRoot->addChild(root, 0);
        splitNode(newRoot, 0);
        root = newRoot;
        this->rootnodes[key] = root;
    }
}

template <typename T>
void IBPTree::insertIter(Node* node, dtp::Interval interval, T& data) {
    if(node->getIsLeaf()) {
        node->addData(interval, data);
    } else {
        int childnum = 0;
        while(childnum < node->getKeys().size() && interval.first > node->getKeys()[childnum].first.first) {
            childnum++;
        }
        insertIter(node->getChild(childnum), interval, data);
        if(node->getChild(childnum)->getKeys().size() == this->order) {
            splitNode(node, childnum);
        }
    }
}

void IBPTree::splitNode(Node* parent, int index) {
    // std::cout << "Splitting node " << parent->keysToString() << " at index " << index << "\n";
    Node* child = parent->getChild(index);
    Node* newChild = new Node(this->order);
    int mid = ((this->order+2-1)/2); // value for order=6

    // move overflowing keys to new child node (and resize the original node)
    newChild->setIsLeaf(child->getIsLeaf());
    newChild->assignKeys(child->getKeys().begin() + mid, child->getKeys().end());
    child->resizeKeys(); // resize the original node

    // update parent
    parent->addChild(newChild, index + 1);
    parent->addKey({child->updateKey(), nullptr}, index);

    if(child->getIsLeaf()) {
        newChild->setNext(child->getNext());
        child->setNext(newChild);
    } else {
        newChild->assignKeys(child->getKeys().begin() + mid, child->getKeys().end());
        child->resizeChildren(mid + 1);
    }
}






