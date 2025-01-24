#include "genogrove/IBPTree.hpp"


namespace genogrove {
    // constructor
    IBPTree::IBPTree(int k) : order(k), rootnodes{}, rightMostNode{} {}
    IBPTree::IBPTree(): order(3), rootnodes{}, rightMostNode{} {}
    IBPTree::~IBPTree() {}

    int IBPTree::getOrder() { return this->order; }
    void IBPTree::setOrder(int k) { this->order = k; }
    std::map<std::string, Node*> IBPTree::getRootnodes() { return this->rootnodes; }
    void IBPTree::setRootnodes(std::map<std::string, Node*> rootnodes) { this->rootnodes = rootnodes; }
    Node* IBPTree::getRightMostNode(std::string chrom) { return this->rightMostNode[chrom]; }
    void IBPTree::setRightMostNode(std::string chrom, Node* node) { this->rightMostNode[chrom] = node; }

    Node* IBPTree::getRoot(std::string key) {
        Node *root = nullptr;
        // check if there is a root node for the given key
        if (this->rootnodes.find(key) != this->rootnodes.end()) {
            root = this->rootnodes[key];
        }
        return root;
    }

    Node* IBPTree::insertRoot(std::string chrom) {
        Node* root = new Node(this->order);
        root->setIsLeaf(true); // root node becomes a leaf node
        this->rootnodes.insert(std::make_pair(chrom, root));
        this->rightMostNode.insert(std::make_pair(chrom, root)); // set as the right most node
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
        if(!node) { throw std::runtime_error("Null node in insertIter"); }

        if(node->getIsLeaf()) {
            try {
//                std::cout << "Inserting key into leaf node with "
//                          << node->getKeys().size() << " keys (max: " << this->order << ")" << std::endl;
                node->insertKey(key);
            } catch (const std::exception& e) {
                std::cerr << "Failed to insert key into leaf node: " << e.what() << std::endl;
                throw;
            }
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
        child->getKeys().resize(mid); // resize the original node

        // update parent (new child node)
        parent->getChildren().insert(parent->getChildren().begin() + index + 1, newChild);
        Key parentKey(child->calcParentKey()); // create a new key for the parent
        parent->getKeys().insert(parent->getKeys().begin() + index, parentKey);

        if(child->getIsLeaf()) {
            newChild->setNext(child->getNext());
            child->setNext(newChild);

            // update rightMostNode if necessaru
            for(auto& [chrom, rightmost] : this->rightMostNode) {
                if(rightmost == child) {
                    this->rightMostNode[chrom] = newChild;
                    break;
                }
            }
        } else {
            newChild->getChildren().assign(child->getChildren().begin() + mid, child->getChildren().end());
            child->getChildren().resize(mid + 1);
        }
    }

    void IBPTree::insertSorted(std::string chrom, Key& key) {
        // get the root node for the given chromosome (or create a new tree if it does not exist)
        Node* root = getRoot(chrom);
        if(root == nullptr) {
            root = insertRoot(chrom);
            insertIter(root, key); // For the first key, use regular insert
            return;
        }

        // get the rightmost node and check if the key is sorted (greater than the rightmost key)
        Node* rightMost = getRightMostNode(chrom);
        if(!rightMost->getKeys().empty() &&
           key.getInterval() <= rightMost->getKeys().back().getInterval()) {
            throw std::runtime_error("Key with Interval: " + key.getInterval().toString() + " is not sorted");
        }

        // insert the key into the rightmost node
        rightMost->insertKey(key); // insert the key into the rightMost node
        if(rightMost->getKeys().size() == this->order) {
            splitNodeSorted(rightMost, chrom);
        }
    }

    void IBPTree::splitNodeSorted(Node* node, const std::string& chrom) {
        if(node == rootnodes[chrom]) { // if node is root - use regular split operation
            Node* newRoot = new Node(this->order);
            newRoot->addChild(node, 0);
            splitNode(newRoot, 0);
            rootnodes[chrom] = newRoot;
            return;
        }

        int childnum = 0;
        while(childnum < node->getParent()->getChildren().size()) {
            if(node->getParent()->getChild(childnum) == node) {
                break;
            }
            childnum++;
        }

        // split the node
        splitNode(node->getParent(), childnum);
        if(node->getParent()->getChildren().size() == this->order) {
            splitNodeSorted(node->getParent(), chrom);
        }
    }

    dtp::Hits IBPTree::overlaps(dtp::Coordinate& query) {
        dtp::Hits hits(query);
        Node* root = getRoot(query.chromosome);
        if(root == nullptr) { return hits; } // return empty vector, as there is no root node for the given key
        searchIter(root, query, hits);

//        AnyVector searchResult{};
//
//        Node* root = getRoot(key); // get the root node
//        if(root == nullptr) { return searchResult; } // return empty vector, as there is no root node for the given key
//        searchIter(root, interval, searchResult);
//        return searchResult;

        return hits;
    }

    dtp::Hits IBPTree::overlaps(std::string chrom, char strand, Interval interval) {
        dtp::Coordinate query(chrom, strand, interval);
        dtp::Hits hits(query);
        Node* root = getRoot(query.chromosome);
        if(root == nullptr) { return hits; }
        searchIter(root, query, hits);
        return hits;
    }

    void IBPTree::searchIter(Node* node, const dtp::Coordinate& query, dtp::Hits& hits) {
        if(node->getIsLeaf()) {
//            std::cout << "searchIter: leaf node" << std::endl;
//            std::cout << "searchIter: interval: " << interval.getStart() << "," << interval.getEnd() << std::endl;

            int lastMatch = -1;
//            std::cout << "iterate through keys" << std::endl;
            for(int i = 0; i < node->getKeys().size(); ++i) {
//                std::cout << "key: " << node->getKeys()[i].getInterval().getStart() << "," << node->getKeys()[i].getInterval().getEnd() << std::endl;
                if(Interval::overlap(node->getKeys()[i].getInterval(), query.interval)) {
                    lastMatch = i;
                    hits.addHit(dtp::Hit(
                            dtp::Coordinate(
                                    query.chromosome,
                                    node->getKeys()[i].getStrand(),
                                    node->getKeys()[i].getInterval()
                            ), // coordinate
                            node->getKeys()[i].getData())); // data

//                    std::cout << "overlap found" << std::endl;
//                    searchResult.push_back(node->getKeys()[i].getData());
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
            if(node->getKeys()[0].getInterval().leftOf(query.interval)) { return; } // check if interval is left of first key

            int i = 0;
            while(i < node->getKeys().size() &&
                  (query.interval.getStart() > node->getKeys()[i].getInterval().getStart() &&
                   query.interval.getStart() > node->getKeys()[i].getInterval().getEnd())) { i++; }
            if(node->getChildren()[i] != nullptr) {
                searchIter(node->getChildren()[i], query, hits);
            }
        }
    }

    void IBPTree::serialize(std::ostream& os) const {
        // write the order of the tree
        os.write(reinterpret_cast<const char*>(&this->order), sizeof(this->order));

        // write the root nodes
        size_t numberRootNodes = this->rootnodes.size();
        os.write(reinterpret_cast<const char*>(&numberRootNodes), sizeof(numberRootNodes));

        // serialize the rootnodes
        for(const auto& [chr, rootnode] : this->rootnodes) {
            size_t chrNameLength = chr.size();
            os.write(reinterpret_cast<const char*>(&chrNameLength), sizeof(chrNameLength));
            os.write(chr.c_str(), chrNameLength); // write the chromosome name
            rootnode->serialize(os); // serialize the rootnode and its subtree
        }
    }

    IBPTree IBPTree::deserialize(std::istream& is) {
        int order;
        is.read(reinterpret_cast<char*>(&order), sizeof(order));
        IBPTree tree(order);

        size_t rootnodeCount;
        is.read(reinterpret_cast<char*>(&rootnodeCount), sizeof(rootnodeCount));

        for(size_t i=0; i < rootnodeCount; ++i) {
            size_t chrNameLength;
            is.read(reinterpret_cast<char*>(&chrNameLength), sizeof(chrNameLength));
            std::string chrName(chrNameLength, '\0');
            is.read(&chrName[0], chrNameLength);

            tree.rootnodes[chrName] = Node::deserialize(is, order);
        }

        tree.rebuildNext(); // rebuild the next pointers of the nodes

        return std::move(tree);
    }

    void IBPTree::rebuildNext() {
        for(auto& [chr, root] : this->rootnodes) {
            rebuildNextSubTree(root);
        }
    }

    void IBPTree::rebuildNextSubTree(Node* node) {
        if(node == nullptr) { return; }
        // if the node is a leaf, then there is no need to go deeper
        if(!node->getIsLeaf()) {
            node->setNext(nullptr);
            Node* prev = nullptr;

            // traverse through the children (of the current node)
            for(auto* child : node->getChildren()) {
                if(child != nullptr) {
                    rebuildNextSubTree(child);

                    // if the child is a leaf, the link it to the previous node
                    if(child->getIsLeaf()) {
                        if(prev != nullptr) {
                            prev->setNext(child);
                        }
                        prev = child;
                    }
                }
            }
        }
    }



    void IBPTree::store(std::string filename) {
        std::ofstream ofs(filename, std::ios::binary);
        this->serialize(ofs);
    }

    IBPTree IBPTree::load(std::string filename) {
        std::ifstream ifs(filename, std::ios::binary);
        return genogrove::IBPTree::deserialize(ifs);
    }

    void IBPTree::exportTreeSIF(std::string filename) {
        std::ofstream ofs(filename);

//        for(auto& [chrom, root] : this->rootnodes) {
//            // traverse through the trees
//            std::cout << "chrom: " << chrom << std::endl;
//            ofs <<
//
//
//
//
//
//        }
    }




//    void IBPTree::printTree() {
//
//    }

} // namespace

