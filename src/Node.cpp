#include "Node.hpp"

template <typename T>
Data::Data(dtp::Interval interval, T data) : interval(interval), data(data) {}

// constructor
Node::Node(int k) : order(k), keys{}, children{}, next{}, isLeaf{false}   {}