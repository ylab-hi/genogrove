#include "Node.hpp"

template <typename T>
Data::Data(dtp::Interval interval, T data) : interval(interval), data(data) {}

// constructor
Node::Node(int k) : order(k), keys{}, children{}, next{}, isLeaf{false}   {}


// getter & setter
std::vector<std::pair<dtp::Interval, Node*>> Node::getKeys() { return this->keys; }
void Node::setIsLeaf(bool leaf) { this->isLeaf = leaf; }
bool Node::getIsLeaf() { return this->isLeaf; }

void Node::addChild(Node *child) { this->children.push_back(child); }
Node* Node::getChild(int index) { return this->children[index]; }
