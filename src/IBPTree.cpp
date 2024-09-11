#include "genogrove/IBPTree.hpp"

namespace genogrove {
    // constructor
    IBPTree::IBPTree(int k) : order(k), rootnodes{} {}
    IBPTree::~IBPTree() {}

    int IBPTree::getOrder() { return this->order; }
    void IBPTree::setOrder(int k) { this->order = k; }
    std::map<std::string, Node*> IBPTree::getRootnodes() { return this->rootnodes; }
    void IBPTree::setRootnodes(std::map<std::string, Node*> rootnodes) { this->rootnodes = rootnodes; }

    Node* IBPTree::getRoot(std::string key) {
        Node *root = nullptr;
        // check if there is a root node for the given key
        if (this->rootnodes.find(key) != this->rootnodes.end()) {
            root = this->rootnodes[key];
        }
        return root;
    }

    Node* IBPTree::insertRoot(std::string key) {
        Node* root = new Node(this->order);
        root->setIsLeaf(true); // root node becomes a leaf node
        this->rootnodes.insert(std::make_pair(key, root));
        return root;
    }

    void IBPTree::insert(std::string chrom, Key& key) {
        // get the root node for the given chromosome (or create a new tree if it does not exist)
        Node* root = getRoot(chrom);
        if(root == nullptr) { root = insertRoot(chrom);}
        insertIter(root, key);
        if(root->getKeys().size() == this->order) {
            Node* newRoot = new Node(this->order);
            newRoot->addChild(root, 0);
            //root->setIsLeaf(false); //
            splitNode(newRoot, 0);
            root = newRoot;
            this->rootnodes[chrom] = root;
        }
    }

    void IBPTree::insertIter(Node* node, Key& key) {
        if(node->getIsLeaf()) {
            node->insertKey(key);
        } else {
            int childnum = 0;
            while(childnum < node->getKeys().size() && key > node->getKeys()[childnum]) { childnum++; }
            insertIter(node->getChild(childnum), key);
            if(node->getChild(childnum)->getKeys().size() == this->order) {
                splitNode(node, childnum);
            }
        }
    }

    void IBPTree::splitNode(Node* parent, int index) {
        Node* child = parent->getChild(index);
        Node* newChild = new Node(this->order);
        int mid = ((this->order+2-1)/2); // value for order=6

        // move overflowing keys to new child node (and resize the original node)
        newChild->setIsLeaf(child->getIsLeaf());
        newChild->getKeys().assign(child->getKeys().begin() + mid, child->getKeys().end());
        child->getKeys().resize(this->order-1); // resize the original node

        // update parent (new child node)
        parent->getChildren().insert(parent->getChildren().begin() + index + 1, newChild);
        Key parentKey(child->calcParentKey()); // create a new key for the parent
        parent->getKeys().insert(parent->getKeys().begin() + index, parentKey);

        if(child->getIsLeaf()) {
            newChild->setNext(child->getNext());
            child->setNext(newChild);
        } else {
            newChild->getChildren().assign(child->getChildren().begin() + mid, child->getChildren().end());
            child->getChildren().resize(mid + 1);
        }
    }

    AnyVector IBPTree::overlaps(std::string key, Interval interval) {
        AnyVector searchResult{};
//
        Node* root = getRoot(key); // get the root node
        if(root == nullptr) { return searchResult; } // return empty vector, as there is no root node for the given key
        searchIter(root, interval, searchResult);



//        std::cout << "search result size: " << searchResult.size() << std::endl;
//        // cast the data to the correct type
//        for(auto& data : searchResult) {
//            // cast the data to the correct type
//            std::type_index dataTypeName = data->getDataType();
//            std::any dataTypes = TypeRegistry::cast(data, dataTypeName);
//            searchResultTyped.push_back(dataTypes);
//        }
//        return searchResultTyped;
        return searchResult;
    }

    void IBPTree::searchIter(Node* node, const Interval& interval, AnyVector& searchResult) {
        if(node->getIsLeaf()) {
//            std::cout << "searchIter: leaf node" << std::endl;
//            std::cout << "searchIter: interval: " << interval.getStart() << "," << interval.getEnd() << std::endl;

            int lastMatch = -1;
//            std::cout << "iterate through keys" << std::endl;
            for(int i = 0; i < node->getKeys().size(); ++i) {
//                std::cout << "key: " << node->getKeys()[i].getInterval().getStart() << "," << node->getKeys()[i].getInterval().getEnd() << std::endl;
                if(Interval::overlap(node->getKeys()[i].getInterval(), interval)) {
                    lastMatch = i;
//                    std::cout << "overlap found" << std::endl;
                    searchResult.push_back(node->getKeys()[i].getData());
                }
            }

            // check if the intervals overlaps with the next node (if so then search the next node)
//            if(node->getNext() != nullptr) {
//                int lastKey = node->getKeys().size()-1;
//                if(Interval::overlap(node->getKeys()[lastKey].getInterval(), interval)) {
//                    std::cout << "search next node" << std::endl;
//                    // iterate through the next node keys
//                    for(auto& key : node->getNext()->getKeys()) {
//                        std::cout << "key: " << key.getInterval().getStart() << "," << key.getInterval().getEnd() << std::endl;
//                    }
//
//
//
//                    //searchIter(node->getNext(), interval, searchResult);
//                }
//            }
        } else {
            if(node->getKeys()[0].getInterval().leftOf(interval)) { return; } // check if interval is left of first key

            int i = 0;
            while(i < node->getKeys().size() &&
                  (interval.getStart() > node->getKeys()[i].getInterval().getStart() &&
                   interval.getStart() > node->getKeys()[i].getInterval().getEnd())) { i++; }
            if(node->getChildren()[i] != nullptr) {
                searchIter(node->getChildren()[i], interval, searchResult);
            }
        }
    }
} // namespace

