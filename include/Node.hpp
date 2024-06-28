#ifndef IBPTREE_NODE_HPP
#define IBPTREE_NODE_HPP

// Standard
#include <iostream>
#include <vector>

// Class
#include "DataTypes.hpp"

class Data {
    public:
        template <typename T>
        Data(dtp::Interval interval, T data);
        ~Data();

        // operator overloading
        bool operator<(const dtp::Interval& other) const;
        bool operator>(const dtp::Interval& other) const;

        // getter & setter
        dtp::Interval getInterval();
        void setInterval(dtp::Interval interval);
        template <typename T>
        T getData();
        void setData(T data);

        // operations

    private:
        dtp::Interval interval; // interval of the data
        template <typename T>
        T data; // data of the Node
};


class Node {
    public:
        Node(int k); // create a new Node with a given order k
        ~Node(); // destructor

        // getter & setter
        int getOrder();
        void setOrder(int k);
        std::vector<std::pair<dtp::Interval, Node*>> getKeys();

        std::vector<Node*> getChildren();


        void setIsLeaf(bool leaf);
        bool getIsLeaf();

        // operations
        void addChild(Node* child);



    private:
        int order; // order of the Node
        std::vector<std::pair<dtp::Interval, Node*>> keys;
        std::vector<Node*> children; // children of the Node
        Node* next;
        bool isLeaf; // is the Node a leaf
};

#endif //IBPTREE_NODE_HPP
