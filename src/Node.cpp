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
    void Node::serialize(std::ostream& os) {
        std::cout << "serialize node" << std::endl;
        os.write(reinterpret_cast<const char*>(&this->isLeaf), sizeof(this->isLeaf)); // write ifLeaf

        size_t numberKeys = this->keys.size(); // write the number of keys
        os.write(reinterpret_cast<const char*>(&numberKeys), sizeof(numberKeys));

        std::cout << "\titerate through keys" << std::endl;
        for(auto& key : this->getKeys()) { // write each key
            std::cout << "\t\tkey: " << key.getInterval().getStart() << "," << key.getInterval().getEnd() << std::endl;
            key.serialize(os);
        }

        // if not a leaf, serialize child nodes
        if(!this->isLeaf) {
            size_t numberChildren = this->children.size(); // write number of children
            os.write(reinterpret_cast<const char*>(&numberChildren), sizeof(numberChildren));

            for(int i=0; i < numberChildren; ++i) {
                std::cout << "\t\tserialize child: " << i << std::endl;
                this->getChildren()[i]->serialize(os);
            }
        }
    }

    Node* Node::deserialize(std::istream& is, int order) {
        std::cout << "deserialize node" << std::endl;
        Node* node = new Node(order); // new node with given order
        is.read(reinterpret_cast<char*>(&node->isLeaf), sizeof(node->isLeaf)); // deserialize ifLeaf

        size_t numberKeys; // deserialize the number of keys in the node
        is.read(reinterpret_cast<char*>(&numberKeys), sizeof(numberKeys));

        // deserialize each key and
        std::cout << "\tnumberKeys: " << numberKeys << std::endl;
        for(size_t i=0; i < numberKeys; i++) { // read each key
            std::cout << "\tdeserialize key: " << i << std::endl;
            node->getKeys().push_back(Key::deserialize(is));
        }

        std::cout << "\tifleaf: " << node->getIsLeaf() << std::endl;

        if(!node->getIsLeaf()) {
            std::cout << "\tdeserialize children" << std::endl;
            size_t numberChildren;
            is.read(reinterpret_cast<char*>(&numberChildren), sizeof(numberChildren));

            std::cout << "\tnumberChildren: " << numberChildren << std::endl;

            for(size_t i=0; i < numberChildren; ++i) {
                node->getChildren().push_back(Node::deserialize(is, order));
            }
        }
        return node;
    }
}


