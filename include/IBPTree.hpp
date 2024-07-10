#ifndef IBPTREE_IBPTREE_HPP
#define IBPTREE_IBPTREE_HPP

// Standard
#include <map>

// Class
#include "Node.hpp"
#include "DataTypes.hpp"

class IBPTree {
    public:
        IBPTree(int k); // create a new IBPTree with a given order k
        ~IBPTree(); // destructor

        // getter & setter
        int getOrder();
        void setOrder(int k);
        std::map<std::string, Node*> getRootnodes();
        void setRootnodes(std::map<std::string, Node*> rootnodes);

        /*
         * @brief get the root node of the IBPTree for a given key (or create a new one)
         * @param the key associated with the root node
         */
        Node* getRoot(std::string key);

        /*
         * @brief insert a new data element into the IBPTree
         * @param the data element to insert
         */
        void insert(std::string key, dtp::Interval interval, std::shared_ptr<void> data);
        void insertIter(Node* node, dtp::Interval interval, std::shared_ptr<void> data);
        /*
         * @brief split a node in the IBPTree
         */
        void splitNode(Node* parent, int index);

        std::vector<std::shared_ptr<void>> search(std::string key, dtp::Interval interval);
        void searchIter(Node* node, const dtp::Interval& interval, std::vector<std::shared_ptr<void>>& searchResult);

        // operations
        bool overlaps(dtp::Interval interval1, dtp::Interval interval2);

        /*
         *
         */
        void tree2SIF(std::string filename);

    private:
        std::map<std::string, Node*> rootnodes; // root nodes of the IBPTree
        int order; // order of the IBPTree
};

#endif //IBPTREE_IBPTREE_HPP
