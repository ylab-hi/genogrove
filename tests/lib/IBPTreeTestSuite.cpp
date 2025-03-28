#include <gtest/gtest.h>
#include "genogrove/Grove.hpp"

#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <filesystem>

namespace fs = std::filesystem;
namespace ggt = genogrove::type;
namespace ggs = genogrove::structure;

TEST(IBPTreeTestSuite, intersectGrove) {
    std::srand(std::time(nullptr));
    int k = 5;
    genogrove::structure::Grove grove(k);

    // intervals to insert
    struct entry {
        ggt::Interval interval;
        std::string chrom;
        char strand;
        std::string

        entry::entry(ggt::Interval intvl, std::string chrom, char strand, std::string data) {
            this->interval = intvl;
            this->chrom = chrom;
            this->strand = strand;
            this->data = data;
        }
    };

    std::vector<std::pair<ggt::Interval, entry>> intervals;
    ggt::TypeRegistry::registerType<std::string>();
    intervals.push_back()





    // register types with the TypeRegistry
    genogrove::TypeRegistry::registerType<int>();
    intervals.push_back({{0, 10}, rand() % 100});
    for(size_t i=11; i < 10000000; i+=10) {
        intervals.push_back({{i, i+9}, rand() % 100});
    }
    auto startInsertion = std::chrono::steady_clock::now();
    std::cout << "#### Inserting data into the tree ####\n";
    for(auto& intvl : intervals) {
        tree.insertData("chr1", intvl.first, intvl.second);
    }
    auto endInsertion = std::chrono::steady_clock::now();
    std::chrono::duration<double> insertionDuration = endInsertion - startInsertion;
    std::cout << "Time taken for insertion: " << insertionDuration.count() << " seconds\n";

    std::cout << "#### Searching for data within the tree ####\n";
    auto startSearch = std::chrono::steady_clock::now();

    for(auto& intvl : intervals) {
//        std::cout << "Searching for interval [" << intvl.first.getStart() << "," << intvl.first.getEnd() << "]";
//        std::cout << " with the data: " << intvl.second << "\n";
        auto searchResult = tree.overlaps("chr1", '+', intvl.first);
        EXPECT_EQ(searchResult.hits.size(), 1) << "The search result for interval [" << intvl.first.getStart()
                                          << "," << intvl.first.getEnd() << "] was not correct (count mismatch)";

        // cast the data to the correct type
        // check if the type is correct
        if(genogrove::TypeRegistry::checktype<int>(searchResult.hits[0].data)) {
            int typed = genogrove::TypeRegistry::cast<int>(searchResult.hits[0].data);
            EXPECT_EQ(typed, intvl.second) << "The search result for interval [" << intvl.first.getStart()
                << "," << intvl.first.getEnd() << "] was not correct (data mismatch)";
        }
    }
    auto endSearch = std::chrono::steady_clock::now();
    std::chrono::duration<double> searchDuration = endSearch - startSearch;
    std::cout << "Time taken for search: " << searchDuration.count() << " seconds\n\n";
}


TEST(IBPTreeTestSuite, CreateTreeFromBED) {
    std::srand(std::time(nullptr));

    // Define a range of k values to test the order
    std::vector<int> k_values = {3, 4, 5, 6, 7, 8, 9, 10, 15, 20, 25, 30, 35, 40, 45, 50}; // Adjust this list as needed

    std::cout << "k, Insertion Time (s), Search Time (s)\n"; // Header for Excel
    genogrove::TypeRegistry::registerType<int>();

    // read in bedfile
    std::string filename = ""





//    std::string filename = "/bedfiles/bed_2M_sorted.bed";

    std::string filename = "/bedfiles/ref/100.bed";

    for (int k : k_values) {
        genogrove::IBPTree tree(k);

        // Check if file exists and can be opened
        std::ifstream infile(filename);
        if (!infile.is_open()) {
            std::cerr << "Failed to open file: " << filename << std::endl;
            FAIL() << "Could not open input file";
            continue;
        }

        auto startInsertion = std::chrono::steady_clock::now();
        std::string line;
        while (std::getline(infile, line)) {
            std::istringstream iss(line);
            std::string chrom;
            int start, end, data;
            iss >> chrom >> start >> end;
            data = 1;
            tree.insertData(chrom, genogrove::Interval{size_t(start), size_t(end)}, data);
        }
        auto endInsertion = std::chrono::steady_clock::now();
        std::chrono::duration<double> insertionDuration = endInsertion - startInsertion;


        // iterate through different files

        std::vector<std::pair<std::string, std::string>> filenames = {
                {"perfect", "/bedfiles/basic/query/perfect/100_100p.bed"},
                {"5p-partial", "/bedfiles/basic/query/5p-partial/100_100p.bed"},
                {"3p-partial", "/bedfiles/basic/query/3p-partial/100_100p.bed"},
                {"contained", "/bedfiles/basic/query/contained/100_100p.bed"},
                {"enclosed", "/bedfiles/basic/query/enclosed/100_100p.bed"},
                {"perfect-gap", "/bedfiles/basic/query/perfect-gap/100_100p.bed"},
                {"left-adjacent-gap", "/bedfiles/basic/query/left-adjacent-gap/100_100p.bed"},
                {"right-adjacent-gap", "/bedfiles/basic/query/right-adjacent-gap/100_100p.bed"},
                {"mid-gap1", "/bedfiles/basic/query/mid-gap1/100_100p.bed"},
                {"mid-gap2", "/bedfiles/basic/query/mid-gap2/100_100p.bed"},
                {"mult", "/bedfiles/complex/query/mult/100_100bin.bed"}
        };

        for(auto& query : filenames) {

            auto startSearch = std::chrono::steady_clock::now();
            std::ifstream infile2(query.second);
            while (std::getline(infile2, line)) {
                std::istringstream iss(line);
                std::string chrom;
                int start, end, data;
                iss >> chrom >> start >> end;
                data = 1;
                auto searchResult = tree.overlaps(chrom, '+', genogrove::Interval{size_t(start), size_t(end)});

                //            EXPECT_EQ(searchResult.hits.size(), 1) << "The search result for interval [" << start << "," << end << "] was not correct (count mismatch)";
                //            if (genogrove::TypeRegistry::checktype<int>(searchResult.hits[0].data)) {
                //                int typed = genogrove::TypeRegistry::cast<int>(searchResult.hits[0].data);
                //            }
            }

            auto endSearch = std::chrono::steady_clock::now();
            std::chrono::duration<double> searchDuration = endSearch - startSearch;

            // Print k, insertion time, and search time in one line for Excel
//            std::cout << k << ", " << filename << ", " << insertionDuration.count() << ", " << searchDuration.count() << "\n";

            std::cout << "100\tbasic\t" << query.first << "\t" << "\t" << searchDuration.count() << "\t" << 0.0 << "\n";
        }
        std::cout << insertionDuration.count() << std::endl;
    }

}





//TEST(IBPTreeTestSuite, CreateTreeSorted) {
//    std::srand(std::time(nullptr));
//
//    genogrove::TypeRegistry::registerType<int>(); // register int type
//
//
//}




//TEST(IBPTreeTestSuite, benchmark) {
//
//    std::vector<int> orders = {20};
//
//    std::vector<std::string> unsorted = {
//            "/Users/sej9799/Documents/projects/gengrove/tests/bedfiles/bed_1K_sorted.bed",
//            "/Users/sej9799/Documents/projects/gengrove/tests/bedfiles/bed_10K_sorted.bed",
//            "/Users/sej9799/Documents/projects/gengrove/tests/bedfiles/bed_100K_sorted.bed",
//            "/Users/sej9799/Documents/projects/gengrove/tests/bedfiles/bed_1M_sorted.bed",
//            "/Users/sej9799/Documents/projects/gengrove/tests/bedfiles/bed_2M_sorted.bed",
//            "/Users/sej9799/Documents/projects/gengrove/tests/bedfiles/bed_3M_sorted.bed",
//            "/Users/sej9799/Documents/projects/gengrove/tests/bedfiles/bed_4M_sorted.bed",
//            "/Users/sej9799/Documents/projects/gengrove/tests/bedfiles/bed_5M_sorted.bed",
//            "/Users/sej9799/Documents/projects/gengrove/tests/bedfiles/bed_6M_sorted.bed",
//            "/Users/sej9799/Documents/projects/gengrove/tests/bedfiles/bed_7M_sorted.bed",
//            "/Users/sej9799/Documents/projects/gengrove/tests/bedfiles/bed_8M_sorted.bed",
//            "/Users/sej9799/Documents/projects/gengrove/tests/bedfiles/bed_9M_sorted.bed",
//            "/Users/sej9799/Documents/projects/gengrove/tests/bedfiles/bed_10M_sorted.bed"
//    };
//
//    genogrove::TypeRegistry::registerType<int>("Int");
//
//
//    std::cout << "unsorted" << std::endl;
//    for(int i=0; i < orders.size(); i++) {
//        std::cout << orders[i] << std::endl;
//
//        for(int j=0; j < unsorted.size(); j++) {
//            auto startInsertion = std::chrono::steady_clock::now();
//            genogrove::Grove tree(orders[i]);
//            std::cout << unsorted[j] << std::endl;
//            std::ifstream infile(unsorted[j]);
//            std::string line;
//            while(std::getline(infile, line)) {
//                std::istringstream iss(line);
//                std::string chrom;
//                int start, end, data;
//                iss >> chrom >> start >> end >> data;
//                genogrove::Interval intvl{size_t(start), size_t(end)};
//                genogrove::Key key{intvl, data};
//                tree.insert(chrom, key);
//            }
//            // time the insertion
//            auto endInsertion = std::chrono::steady_clock::now();
//            std::chrono::duration<double> insertionDuration = endInsertion - startInsertion;
//            std::cout << "Time taken for insertion: " << insertionDuration.count() << " seconds\n\n";
//        }
//    }
//
//
//    // time the search
//
//
//
//
//
//
//}





//TEST(IBPTreeTestSuite, SearchOverlappingIntervals) {
//    std::cout << "#### Searching for overlapping intervals ####\n";
//    std::string filename = "/Users/sej9799/Documents/projects/gengrove/pairs1_9M.bed";
//
//    // time the search
//    auto startInsertion = std::chrono::steady_clock::now();
//
//    genogrove::Grove tree(3);
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