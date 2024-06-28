#include "Node.hpp"

template <typename T>
Data::Data(dtp::Interval interval, T data) : interval(interval), data(data) {}

// constructor
Node::Node(int k) : order(k), keys{}, children{}, next{}, isLeaf{false}   {}


// getter & setter
void Node::setIsLeaf(bool leaf) { this->isLeaf = leaf; }
bool Node::getIsLeaf() { return this->isLeaf; }
