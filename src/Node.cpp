#include "Node.hpp"

// constructor
Node::Node(int k) : order(k), keys{}, children{}, next{}, isLeaf{false}   {}

// getter & setter
int Node::getOrder() { return this->order; }
void Node::setOrder(int k) { this->order = k; }
std::vector<std::shared_ptr<Key>>& Node::getKeys() { return this->keys; }
void Node::setKeys(std::vector<std::shared_ptr<Key>> keys) { this->keys = keys; }
std::vector<Node*>& Node::getChildren() { return this->children; }
void Node::setChildren(std::vector<Node*> children) { this->children = children; }
void Node::setNext(Node* next) { this->next = next; }
Node* Node::getNext() { return this->next; }
void Node::setIsLeaf(bool leaf) { this->isLeaf = leaf; }
bool Node::getIsLeaf() { return this->isLeaf; }

void Node::insertKey(std::shared_ptr<Key> key) {
    int i=0;
    while(i < this->keys.size() && key > this->keys[i]) { i++; }
    this->keys.insert(this->keys.begin() + i, key);
    std::cout << "Inserted key: " << key->getInterval().first << "," << key->getInterval().second << "\n";
}
void Node::insertKey(std::shared_ptr<Key> key, int index) {
    this->keys.insert(this->keys.begin() + index, key);
}
/*
 * Calculates the (parent) node interval based on the keys (of the child)
 */
dtp::Interval Node::calcParentKey() {
    dtp::Interval intvl = {std::string::npos, 0};
    for(int i=0; i < keys.size(); i++) {
        if(keys[i]->getInterval().first < intvl.first) { intvl.first = keys[i]->getInterval().first; }
        if(keys[i]->getInterval().second > intvl.second) { intvl.second = keys[i]->getInterval().second; }
    }
    return intvl;
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
void Node::addChild(Node* child, int index) {
    this->children.insert(this->children.begin() + index, child);
}
Node* Node::getChild(int index) { return this->children[index]; }


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


