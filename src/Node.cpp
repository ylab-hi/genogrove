#include "Node.hpp"

/*
template <typename T>
Data<T>::Data(dtp::Interval interval, T data) : interval(interval), data(data) {}*/

// constructor
template <typename T>
Node<T>::Node(int k) : order(k), keys{}, children{}, next{}, isLeaf{false}   {}

// getter & setter
template <typename T>
int Node<T>::getOrder() { return this->order; }
template <typename T>
void Node<T>::setOrder(int k) { this->order = k; }
template <typename T>
std::vector<std::pair<dtp::Interval, T*>> Node<T>::getKeys() { return this->keys; }
template <typename T>
void Node<T>::setKeys(std::vector<std::pair<dtp::Interval, T*>> keys) { this->keys = keys; }
template <typename T>
std::vector<Node<T>*> Node<T>::getChildren() { return this->children; }
template <typename T>
void Node<T>::setChildren(std::vector<Node*> children) { this->children = children; }
template <typename T>
void Node<T>::setNext(Node* next) { this->next = next; }
template <typename T>
Node<T>* Node<T>::getNext() { return this->next; }
template <typename T>
void Node<T>::setIsLeaf(bool leaf) { this->isLeaf = leaf; }
template <typename T>
bool Node<T>::getIsLeaf() { return this->isLeaf; }

template <typename T>
void Node<T>::addKey(std::pair<dtp::Interval, Node*> key, int index) {
    this->keys.insert(this->keys.begin() + index, key);
}
template <typename T>
void Node<T>::assignKeys(std::vector<std::pair<dtp::Interval, Node*>>::iterator start,
                      std::vector<std::pair<dtp::Interval, Node*>>::iterator end) {
    this->keys.assign(start, end);
}

/*
 * This method moves the keys from one node to another
 */
template <typename T>
void Node<T>::moveKeys(int mid, Node* child) {
    this->keys.assign(child->getKeys().begin() + mid, child->getKeys().end());
}
template <typename T>
void Node<T>::resizeKeys() { this->keys.resize(this->order-1); }

template <typename T>
dtp::Interval Node<T>::updateKey() {
    dtp::Interval intvl = {std::string::npos, 0};
    for(int i=0; i < keys.size(); i++) {
        if(keys[i].first.first < intvl.first) { intvl.first = keys[i].first.first; }
        if(keys[i].first.second > intvl.second) { intvl.second = keys[i].first.second; }
    }
    return intvl;
}

template <typename T>
void Node<T>::assignChilds(std::vector<Node*>::iterator start,
                        std::vector<Node*>::iterator end) {
    this->children.assign(start, end);
}
template <typename T>
void Node<T>::addChild(Node<T> *child, int index) {
    this->children.insert(this->children.begin() + index, child);
}
template <typename T>
void Node<T>::resizeChildren(int size) { this->children.resize(size); }
template <typename T>
Node<T>* Node<T>::getChild(int index) { return this->children[index]; }

/*
 * This method adds a new data element to the Node. It compares the intervals of the node
 */
template <typename T>
void Node<T>::addData(dtp::Interval interval, T data) {
    int i=0;
    while(i < this->keys.size() && this->keys[i].first.first < interval.first) { i++; }
    this->keys.insert(this->keys.begin() + i, {interval, data});
}





