#include "IBPTree.hpp"

// constructor
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
        this->rootnodes.insert(std::make_pair(key, root));
    } else {
        root = this->rootnodes[key];
    }
    return root;
}

void IBPTree::insert(std::string chrom, Key& key) {
    Node* root = getRoot(chrom);
    insertIter(root, key);
    if(root->getKeys().size() == this->order) {
        Node* newRoot = new Node(this->order);
        newRoot->addChild(root, 0);
//        splitNode(newRoot, 0);
        root = newRoot;
        this->rootnodes[chrom] = root;
    }
}

void IBPTree::insertIter(Node* node, Key& key) {
    if(node->getIsLeaf()) {
        node->insertKey(key);
    }
//        node->addKey(key);
//    } else {
//        int childnum = 0;
//        while(childnum < node->getKeys().size() && interval.first > node->getKeys()[childnum].first.first) {
//            childnum++;
//        }
//        // TODO: add > operator on Key
//        insertIter(node->getChild(childnum), interval, data);
//        if(node->getChild(childnum)->getKeys().size() == this->order) {
//            splitNode(node, childnum);
//        }
//    }
}

//
//void IBPTree::splitNode(Node* parent, int index) {
//    Node* child = parent->getChild(index);
//    Node* newChild = new Node(this->order);
//    int mid = ((this->order+2-1)/2); // value for order=6
//
//    // move overflowing keys to new child node (and resize the original node)
//    newChild->setIsLeaf(child->getIsLeaf());
//    newChild->assignKeys(child->getKeys().begin() + mid, child->getKeys().end());
//    child->resizeKeys(); // resize the original node
//
//    // update parent
//    parent->addChild(newChild, index + 1);
//    parent->addKey({child->updateKey(), nullptr}, index);
//
//    if(child->getIsLeaf()) {
//        newChild->setNext(child->getNext());
//        child->setNext(newChild);
//    } else {
//        newChild->assignKeys(child->getKeys().begin() + mid, child->getKeys().end());
//        child->resizeChildren(mid + 1);
//    }
//}
//
//std::vector<std::shared_ptr<void>> IBPTree::search(std::string key, dtp::Interval interval) {
//    Node* root = getRoot(key);
//    std::vector<std::shared_ptr<void>> searchResult;
//    searchIter(root, interval, searchResult);
//
//    return searchResult;
//}
//
//void IBPTree::searchIter(Node* node, const dtp::Interval& interval, std::vector<std::shared_ptr<void>>& searchResult) {
//    if(node->getIsLeaf()) {
//        for (int i = 0; i < node->getKeys().size(); ++i) {
//            if (overlaps(node->getKeys()[i].first, interval)) {
//                searchResult.push_back(node->getKeys()[i].second);
//            }
//        }
//
//        // check if the intervals overlaps with the next node (if so then search the next node)
//        if (node->getNext() != nullptr) {
//            if (overlaps(node->getKeys()[0].first, interval)) {
//                searchIter(node->getNext(), interval, searchResult);
//            }
//        }
//    } else {
//        int i = 0;
//        while(i < node->getKeys().size() &&
//              (interval.first > node->getKeys()[i].first.first &&
//               (interval.first > node->getKeys()[i].first.second))){
//            i++;
//        }
//        if(node->getChildren()[i] != nullptr) {
//            searchIter(node->getChildren()[i], interval, searchResult);
//        }
//    }
//}
//
//bool IBPTree::overlaps(dtp::Interval intvl1, dtp::Interval intvl2) {
//    dtp::Interval intvl = {std::max(intvl1.first, intvl2.first),
//                           std::min(intvl1.second, intvl2.second)};
//    return intvl.first <= intvl.second;
//}
//
//
//
//
//
//
//
//
//
//
