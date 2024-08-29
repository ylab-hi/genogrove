#ifndef IBPTREE_IBPTREE_HPP
#define IBPTREE_IBPTREE_HPP

// Standard
#include <map>

// Class
#include "Node.hpp"

namespace genogrove {
    class Node; // forward declaration

    using AnyVector = std::vector<std::shared_ptr<genogrove::AnyBase>>;

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
             * @brief get the root node of the IBPTree for a given key
             * @param the key associated with the root node
             */
            Node* getRoot(std::string key);

            /*
             * @brief insert a new root node into the IBPTree
             */
            Node* insertRoot(std::string key);

            template<typename T>
            void insertData(std::string chrom, Interval intvl, T data) {
                Key key(intvl, data);
                insert(chrom, key);
            }

            /*
             * @brief insert a new data element into the IBPTree
             * @param the data element to insert
             */
            void insert(std::string chrom, Key& key);
            void insertIter(Node* node, Key& key);
            /*
             * @brief split a node in the IBPTree
             */
            void splitNode(Node* parent, int index);

            std::vector<std::any> search(std::string key, Interval interval);
            void searchIter(Node* node, const Interval& interval, AnyVector& searchResult);

            /*
             *
             */
            void tree2SIF(std::string filename);

        private:
            std::map<std::string, Node*> rootnodes; // root nodes of the IBPTree
            int order; // order of the IBPTree
    }; // class
}; // namspace

#endif //IBPTREE_IBPTREE_HPP
