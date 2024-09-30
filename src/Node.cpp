#include "genogrove/Node.hpp"

namespace genogrove {
    // constructor
    Node::Node(int k) : order(k), keys{}, children{}, next{}, isLeaf{false} {}

    // getter & setter
    int Node::getOrder() { return this->order; }
    void Node::setOrder(int k) { this->order = k; }
    std::vector<Key> &Node::getKeys() { return this->keys; }
    void Node::setKeys(std::vector<Key> &keys) { this->keys = keys; }
    std::vector<Node *> &Node::getChildren() { return this->children; }
    void Node::setChildren(std::vector<Node *> children) { this->children = children; }
    void Node::setNext(Node *next) { this->next = next; }
    Node *Node::getNext() { return this->next; }
    void Node::setIsLeaf(bool leaf) { this->isLeaf = leaf; }
    bool Node::getIsLeaf() { return this->isLeaf; }

    void Node::insertKey(Key &key) {
        int i = 0;
        while (i < this->keys.size() && key.getInterval() > this->keys[i].getInterval()) { i++; }
        this->keys.insert(this->keys.begin() + i, key);
    }

    void Node::insertKey(Key &key, int index) {
        this->keys.insert(this->keys.begin() + index, key);
    }

    /*
     * Calculates the (parent) node interval based on the keys (of the child)
     */
    Interval Node::calcParentKey() {
        Interval intvl{std::string::npos, 0};
        for (int i = 0; i < keys.size(); i++) {
            if (keys[i].getInterval().getStart() < intvl.getStart()) {
                intvl.setStart(keys[i].getInterval().getStart());
            }
            if (keys[i].getInterval().getEnd() > intvl.getEnd()) { intvl.setEnd(keys[i].getInterval().getEnd()); }
        }
        return intvl;
    }

    void Node::addChild(Node *child, int index) {
        this->children.insert(this->children.begin() + index, child);
    }
    Node *Node::getChild(int index) { return this->children[index]; }

    // serialize the node
    void Node::serialize(std::ostream& os) const {
        // write ifLeaf
        os.write(reinterpret_cast<const char*>(&this->isLeaf), sizeof(this->isLeaf));

        // write number of keys
        size_t numberKeys = this->keys.size();
        os.write(reinterpret_cast<const char*>(&numberKeys), sizeof(numberKeys));

        // write each key
        for(auto& key : this->keys) {
            key.serialize(os);
        }

        // if not a leaf, serialize child nodes
        if(!this->isLeaf) {
            for(const auto& child : children) {
                child->serialize(os);
            }
        }
    }

    Node* Node::deserialize(std::istream& is, int order) {
        Node* node = new Node(order);

        // read if the node is a leaf
        is.read(reinterpret_cast<char*>(&node->isLeaf), sizeof(node->isLeaf));

        // read the number of keys
        size_t numberKeys;
        is.read(reinterpret_cast<char*>(&numberKeys), sizeof(numberKeys));

        for(size_t i=0; i < numberKeys; i++) { // read each key
            node->keys.push_back(Key::deserialize(is));
        }

        if(!node->isLeaf) {
            for(size_t i=0; i < order; ++i) {
                node->children.push_back(Node::deserialize(is, order));
            }
        }
    }
}

/*
void Node::updateKey(Node* node) {
    dtp::Interval intvl = {std::string::npos, 0};
    for(int i=0; )

}
*/


//void Node::assignKeys(std::vector<std::pair<dtp::Interval, std::shared_ptr<void>>>::iterator start,
//                      std::vector<std::pair<dtp::Interval, std::shared_ptr<void>>>::iterator end) {
//    this->keys.assign(start, end);
//}
//
///*
// * This method moves the keys from one node to another
// */
//void Node::moveKeys(int mid, Node* child) {
//    this->keys.assign(child->getKeys().begin() + mid, child->getKeys().end());
//}
//void Node::resizeKeys() { this->keys.resize(this->order-1); }
//
//dtp::Interval Node::updateKey() {
//    dtp::Interval intvl = {std::string::npos, 0};
//    for(int i=0; i < keys.size(); i++) {
//        if(keys[i].first.first < intvl.first) { intvl.first = keys[i].first.first; }
//        if(keys[i].first.second > intvl.second) { intvl.second = keys[i].first.second; }
//    }
//    return intvl;
//}
//
//void Node::assignChilds(std::vector<Node*>::iterator start,
//                        std::vector<Node*>::iterator end) {
//    this->children.assign(start, end);
//}


//void Node::resizeChildren(int size) { this->children.resize(size); }
//
///*
// * This method adds a new data element to the Node. It compares the intervals of the node
// */
///*
//void Node::addData(dtp::Interval interval, std::shared_ptr<void> data) {
//    int i=0;
//    while(i < this->keys.size() && this->keys[i].first.first < interval.first) { i++; }
//    this->keys.insert(this->keys.begin() + i, {interval, data});
//}*/
//
//
//




