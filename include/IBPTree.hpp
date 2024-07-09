#ifndef IBPTREE_IBPTREE_HPP
#define IBPTREE_IBPTREE_HPP

// Standard
#include <map>

// Class
#include "Node.hpp"
#include "DataTypes.hpp"

template <typename T>
class IBPTree {
    public:
        IBPTree(int k); // create a new IBPTree with a given order k
        ~IBPTree(); // destructor

        // getter & setter
        int getOrder();
        void setOrder(int k);
        std::map<std::string, Node<T>*> getRootnodes();
        void setRootnodes(std::map<std::string, Node<T>*> rootnodes);

        /*
         * @brief get the root node of the IBPTree for a given key (or create a new one)
         * @param the key associated with the root node
         */
        Node<T>* getRoot(std::string);

        /*
         * @brief insert a new data element into the IBPTree
         * @param the data element to insert
         */
        void insert(std::string key, dtp::Interval interval, T& data);
        void insertIter(Node<T>* node, dtp::Interval interval, T& data);
        /*
         * @brief split a node in the IBPTree
         */
        void splitNode(Node<T>* parent, int index);

        std::vector<T> search(std::string key, dtp::Interval interval);
        void searchIter(Node<T>* node, const dtp::Interval& interval, std::vector<T>& searchResult);

        // operations
        bool overlaps(dtp::Interval interval1, dtp::Interval interval2);

        /*
         *
         */
        void tree2SIF(std::string filename);

    private:
        std::map<std::string, Node<T>*> rootnodes; // root nodes of the IBPTree
        int order; // order of the IBPTree
};

#endif //IBPTREE_IBPTREE_HPP
