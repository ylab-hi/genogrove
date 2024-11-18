#ifndef IBPTREE_IBPTREE_HPP
#define IBPTREE_IBPTREE_HPP

// Standard
#include <map>
#include <fstream>

// Class
#include "Node.hpp"
#include "Chroms.hpp"
#include "DataTypes.hpp"

namespace genogrove {
    class Node; // forward declaration

    using AnyVector = std::vector<std::shared_ptr<genogrove::AnyBase>>;

    class IBPTree {
        public:
            IBPTree(int k); // create a new IBPTree with a given order k
            IBPTree(); // create a new IBPTree with default order
            ~IBPTree(); // destructor

            // getter & setter
            int getOrder();
            void setOrder(int k);
            std::map<std::string, Node*> getRootnodes();
            void setRootnodes(std::map<std::string, Node*> rootnodes);
            Node* getRightMostNode(std::string chrom);
            void setRightMostNode(std::string chrom, Node* node);

            /*
             * @brief get the root node of the IBPTree for a given key
             * @param the key associated with the root node
             */
            Node* getRoot(std::string key);

            /*
             * @brief insert a new root node into the IBPTree
             */
            Node* insertRoot(std::string key);


            /*
             * @brief insert a new data element into the IBPTree
             * @param chromosome to be inserted
             * @param interval to be inserted
             * @param strand to be inserted
             * @param data to be inserted
             */
            template<typename T>
            void insertData(std::string chrom, Interval intvl, char strand, T data) {
                Key key(intvl, strand, data);
                insert(chrom, key);
            }

            /*
             * @brief insert a new data element into the IBPTree (without data)
             * @param chromosome to be inserted
             * @param interval to be inserted
             * @param strand to be inserted
             */
            void insertData(std::string chrom, Interval intvl, char strand) {
                Key key(intvl, strand, nullptr);
            }


            /*
             * @brief insert a new data element into the IBPTree (sorted)
             */
            template<typename T>
            void insertDataSorted(std::string chrom, Interval intvl, T data) {
                Key key(intvl, data);
                insertSorted(chrom, key);
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

            /*
             * @brief insert a new key into the IBPTree
             */
            void insertSorted(std::string, Key& key);
            /*
             * @brief split a node in the IBPTree (if the inserted key is sorted)
             */
            void splitNodeSorted(Node* node, const std::string& chrom);

            /*
             * @brief determine the overlaps of a query (dtp::Coordinate) within the tree
             */
            dtp::Hits overlaps(dtp::Coordinate& query);

            /*
             * @brief determine the overlaps of a query (chromosome, strand, interval) within the tree
             */
            dtp::Hits overlaps(std::string chrom, char strand, Interval interval);

            /*
             * @brief
             */
            void searchIter(Node* node, const dtp::Coordinate& coordinate, dtp::Hits& hits);

            void serialize(std::ostream& os) const;
            static IBPTree deserialize(std::istream& is);

            /*
             * @brief rebuild the next pointers of the nodes in the tree
             */
            void rebuildNext();

            /*
             * @brief rebuild the next pointers of the nodes in the tree
             */
            void rebuildNextSubTree(Node* node);


            /*
             * @brief store the genogrove index/tree in a (binary) file
             */
            void store(std::string filename);

            /*
             * @brief load the genogrove index/tree from a (binary) file
             */
            static IBPTree load(std::string filename);

            void exportTree(std::string filename, std::string format);

            /*
             * @brief export the tree in the SIF format (for debugging purposes)
             */
            void exportTreeSIF(std::string filename);

            /*
             * @brief prints the tree (cirrently only for debugging purposes)
             */
            void printTree();

        private:
            int order; // order of the IBPTree
            Chroms chroms;
            std::map<std::string, Node*> rootnodes; // root nodes of the IBPTree
            std::map<std::string, Node*> rightMostNode; // right most node of the IBPTree (for easy insertion)
    }; // class
}; // namspace

#endif //IBPTREE_IBPTREE_HPP
