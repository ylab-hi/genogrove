#ifndef IBPTREE_NODE_HPP
#define IBPTREE_NODE_HPP

// Standard
#include <iostream>
#include <vector>
#include <memory>

// Class
#include "Key.hpp"
#include "DataTypes.hpp"

namespace ggt = genogrove::type;

namespace genogrove::structure {
    class Key; // forward declaration
    using KeyPtr = std::shared_ptr<Key>;

    class Node {
        public:
            Node(int k); // create a new Node with a given order k
            ~Node(); // destructor

            // getter & setter
            int getOrder();
            void setOrder(int k);
            std::vector<Key>& getKeys();
            void setKeys(std::vector<Key>& keys);
            std::vector<Node*>& getChildren();
            void setChildren(std::vector<Node*> children);
            Node* getParent();
            void setParent(Node* parent);
            void setNext(Node* next);
            Node* getNext();
            void setIsLeaf(bool leaf);
            bool getIsLeaf();

            /*
             * @brief inserts a new key to the Node
             * @param key the key (Interval, Node) to add
             * @param index the index at which to add the key
             */
            void insertKey(Key& key);
            void insertKey(Key& key, int index);
            /*
             * @brief calculates the (parent) node interval based on the keys (of the child)
             */
            ggt::Interval calcParentKey();
    //
    //        /*
    //         * @brief moves keys from one node to another
    //         * @param mid the index of left-most key to move (until end of vector)
    //         * @param child the node from which to move the keys
    //         */
    //        void moveKeys(int mid, Node* child);
    //        /*
    //         * @brief resize the keys vector (to order-1)
    //         */
    //        void resizeKeys();
    //        /*
    //         * @brief calculates/updates the new key (Interval) of the Node based on the keys
    //         */
    //        dtp::Interval updateKey();
    //
            void addChild(Node* child, int index);
            Node* getChild(int index);

    //        void assignChilds(std::vector<Node*>::iterator start, std::vector<Node*>::iterator end);
    //        void resizeChildren(int size);
    //
    //        void addData(dtp::Interval interval, std::shared_ptr<void> data);

            // serialize the node
            void serialize(std::ostream& os);
            static Node* deserialize(std::istream& is, int order);

            /*
             * @brief prints the keys of the node to an output stream
             */
            void printKeys(std::ostream& os, std::string sep="\t");

        private:
            int order; // order of the Node
            std::vector<Key> keys;
            std::vector<Node*> children; // children of the Node
            Node* parent;
            Node* next;
            bool isLeaf; // is the Node a leaf

    }; // class
} // namespace


#endif //IBPTREE_NODE_HPP
