#include "IBPTree.hpp"

// constructor
template <typename T>
IBPTree<T>::IBPTree(int k) : order(k), rootnodes{} {}
template <typename T>
IBPTree<T>::~IBPTree() {}

template <typename T>
int IBPTree<T>::getOrder() { return this->order; }
template <typename T>
void IBPTree<T>::setOrder(int k) { this->order = k; }
template <typename T>
std::map<std::string, Node<T>*> IBPTree<T>::getRootnodes() { return this->rootnodes; }
template <typename T>
void IBPTree<T>::setRootnodes(std::map<std::string, Node<T>*> rootnodes) { this->rootnodes = rootnodes; }

template <typename T>
Node<T>* IBPTree<T>::getRoot(std::string key) {
    Node<T>* root;
    if(this->rootnodes.find(key) == this->rootnodes.end()) {
        root = new Node<T>(this->order);
        root->setIsLeaf(true); // root node becomes a leaf node
    } else {
        root = this->rootnodes[key];
    }
    return root;
}

template <typename T>
void IBPTree<T>::insert(std::string key, dtp::Interval interval, T& data) {
    Node<T>* root = getRoot(key);
    insertIter(root, data);
    if(root->getKeys().size() == this->order) {
        Node<T>* newRoot = new Node<T>(this->order);
        newRoot->addChild(root, 0);
        splitNode(newRoot, 0);
        root = newRoot;
        this->rootnodes[key] = root;
    }
}

template <typename T>
void IBPTree<T>::insertIter(Node<T>* node, dtp::Interval interval, T& data) {
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

template <typename T>
void IBPTree<T>::splitNode(Node<T>* parent, int index) {
    // std::cout << "Splitting node " << parent->keysToString() << " at index " << index << "\n";
    Node<T>* child = parent->getChild(index);
    Node<T>* newChild = new Node<T>(this->order);
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

template <typename T>
std::vector<T> IBPTree<T>::search(std::string key, dtp::Interval interval) {
    Node<T>* root = getRoot(key);
    std::vector<T> searchResult;
    searchIter(root, interval, searchResult);
}

template <typename T>
void IBPTree<T>::searchIter(Node<T>* node, const dtp::Interval& interval, std::vector<T>& searchResult) {
    if(node->getIsLeaf()) {
        for(int i=0; i < node->getKeys().size(); ++i) {
            if(overlaps(node->getKeys()[i].first, interval)) {
                searchResult.push_back(node->getKeys()[i].second->getData());
            }
        }
    }
}

template <typename T>
bool IBPTree<T>::overlaps(dtp::Interval intvl1, dtp::Interval intvl2) {
    dtp::Interval intvl = {std::max(intvl1.first, intvl2.first),
                           std::min(intvl1.second, intvl2.second)};
    return intvl.first <= intvl.second;
}










