#include <gtest/gtest.h>
#include "genogrove/IBPTree.hpp"

#include <stdlib.h>
#include <fstream>
#include <sstream>

TEST(IBPTreeTestSuite, CreateIBPTree) {
    std::srand(std::time(nullptr));
    int k = 20;
    genogrove::IBPTree tree(k);
    std::vector<std::pair<genogrove::Interval, int>> intervals;

    // register types with the TypeRegistry
    genogrove::TypeRegistry::registerType<int>("Int");

    intervals.push_back({{0, 10}, rand() % 100});
    for(size_t i=11; i < 10000000; i+=10) {
        intervals.push_back({{i, i+9}, rand() % 100});
    }
    auto startInsertion = std::chrono::steady_clock::now();
    std::cout << "#### Inserting data into the tree ####\n";
    for(auto& intvl : intervals) {
        genogrove::Key key{intvl.first, intvl.second};
        tree.insert("chr1", key);
    }
    auto endInsertion = std::chrono::steady_clock::now();
    std::chrono::duration<double> insertionDuration = endInsertion - startInsertion;
    std::cout << "Time taken for insertion: " << insertionDuration.count() << " seconds\n\n";
    std::cout << "#### Searching for data within the tree ####\n";
    auto startSearch = std::chrono::steady_clock::now();
    for(auto& intvl : intervals) {
//        std::cout << "Searching for interval [" << intvl.first.getStart() << "," << intvl.first.getEnd() << "]";
//        std::cout << " with the data: " << intvl.second << "\n";
        auto searchResult = tree.overlaps("chr1", intvl.first);
        EXPECT_EQ(searchResult.size(), 1) << "The search result for interval [" << intvl.first.getStart()
                                          << "," << intvl.first.getEnd() << "] was not correct (count mismatch)";
        // cast the data to the correct type
        std::type_index dataTypeName = searchResult[0]->getDataType();
        int typed = genogrove::TypeRegistry::cast(searchResult[0], dataTypeName);



//        std::any dataTypes = genogrove::TypeRegistry::cast(searchResult[0], dataTypeName);
//        EXPECT_EQ(std::any_cast<int>(dataTypes), intvl.second) << "The search result for interval ["
//            << intvl.first.getStart() << "," << intvl.first.getEnd() << "] was not correct (data mismatch)";






//        EXPECT_EQ(std::any_cast<int>(searchResult[0]), intvl.second) << "The search result for interval ["
//            << intvl.first.getStart() << "," << intvl.first.getEnd() << "] was not correct (data mismatch)";
    }
//    auto endSearch = std::chrono::steady_clock::now();
//    std::chrono::duration<double> searchDuration = endSearch - startSearch;
//    std::cout << "Time taken for search: " << searchDuration.count() << " seconds\n\n";
}


TEST(IBPTreeTestSuite, benchmark) {

    std::vector<int> orders = {20};

    std::vector<std::string> unsorted = {
            "/Users/sej9799/Documents/projects/gengrove/tests/bedfiles/bed_1K_sorted.bed",
            "/Users/sej9799/Documents/projects/gengrove/tests/bedfiles/bed_10K_sorted.bed",
            "/Users/sej9799/Documents/projects/gengrove/tests/bedfiles/bed_100K_sorted.bed",
            "/Users/sej9799/Documents/projects/gengrove/tests/bedfiles/bed_1M_sorted.bed",
            "/Users/sej9799/Documents/projects/gengrove/tests/bedfiles/bed_2M_sorted.bed",
            "/Users/sej9799/Documents/projects/gengrove/tests/bedfiles/bed_3M_sorted.bed",
            "/Users/sej9799/Documents/projects/gengrove/tests/bedfiles/bed_4M_sorted.bed",
            "/Users/sej9799/Documents/projects/gengrove/tests/bedfiles/bed_5M_sorted.bed",
            "/Users/sej9799/Documents/projects/gengrove/tests/bedfiles/bed_6M_sorted.bed",
            "/Users/sej9799/Documents/projects/gengrove/tests/bedfiles/bed_7M_sorted.bed",
            "/Users/sej9799/Documents/projects/gengrove/tests/bedfiles/bed_8M_sorted.bed",
            "/Users/sej9799/Documents/projects/gengrove/tests/bedfiles/bed_9M_sorted.bed",
            "/Users/sej9799/Documents/projects/gengrove/tests/bedfiles/bed_10M_sorted.bed"
    };

    genogrove::TypeRegistry::registerType<int>("Int");


    std::cout << "unsorted" << std::endl;
    for(int i=0; i < orders.size(); i++) {
        std::cout << orders[i] << std::endl;

        for(int j=0; j < unsorted.size(); j++) {
            auto startInsertion = std::chrono::steady_clock::now();
            genogrove::IBPTree tree(orders[i]);
            std::cout << unsorted[j] << std::endl;
            std::ifstream infile(unsorted[j]);
            std::string line;
            while(std::getline(infile, line)) {
                std::istringstream iss(line);
                std::string chrom;
                int start, end, data;
                iss >> chrom >> start >> end >> data;
                genogrove::Interval intvl{size_t(start), size_t(end)};
                genogrove::Key key{intvl, data};
                tree.insert(chrom, key);
            }
            // time the insertion
            auto endInsertion = std::chrono::steady_clock::now();
            std::chrono::duration<double> insertionDuration = endInsertion - startInsertion;
            std::cout << "Time taken for insertion: " << insertionDuration.count() << " seconds\n\n";
        }
    }


    // time the search






}





//TEST(IBPTreeTestSuite, SearchOverlappingIntervals) {
//    std::cout << "#### Searching for overlapping intervals ####\n";
//    std::string filename = "/Users/sej9799/Documents/projects/gengrove/pairs1_9M.bed";
//
//    // time the search
//    auto startInsertion = std::chrono::steady_clock::now();
//
//    genogrove::IBPTree tree(3);
//    genogrove::TypeRegistry::registerType<int>();
//    // iterate through the file
//    std::ifstream infile(filename);
//    std::string line;
//    while(std::getline(infile, line)) {
//        std::istringstream iss(line);
//        std::string chrom;
//        int start, end, data;
//        iss >> chrom >> start >> end >> data;
//        genogrove::Interval intvl{size_t(start), size_t(end)};
//        genogrove::Key key{intvl, data};
//        tree.insert(chrom, key);
//    }
//    // time the insertion
//    auto endInsertion = std::chrono::steady_clock::now();
//    std::chrono::duration<double> insertionDuration = endInsertion - startInsertion;
//    std::cout << "Time taken for insertion: " << insertionDuration.count() << " seconds\n\n";
//
//    auto startSearch = std::chrono::steady_clock::now();
//
//    // search
//    std::string filename2 = "/Users/sej9799/Documents/projects/gengrove/pairs2_9M.bed";
//    std::ifstream infile2(filename2);
//    while(std::getline(infile2, line)) {
//        std::istringstream iss(line);
//        std::string chrom;
//        int start, end, data;
//        iss >> chrom >> start >> end >> data;
//        genogrove::Interval intvl{size_t(start), size_t(end)};
//        auto searchResult = tree.search(chrom, intvl);
//    }
//
//    // time the search
//    auto endSearch = std::chrono::steady_clock::now();
//    std::chrono::duration<double> searchDuration = endSearch - startSearch;
//    std::cout << "Time taken for search: " << searchDuration.count() << " seconds\n\n";
//
//
//}