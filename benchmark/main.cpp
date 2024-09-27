#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "genogrove/all.hpp"
#include <fstream>
#include <sstream>
#include <chrono>

int main() {
    std::cout << "Benchmarking GenoGrove" << std::endl;

    std::vector<int> orders = {20};
//    orders.push_back(20);

    // files to benchmark
    std::vector<std::pair<std::string, std::string>> files;
    files.push_back({"1K", "/Users/sej9799/Documents/projects/gengrove/benchmark/bedfiles/bed_1K_sorted.bed"});
    files.push_back({"10K", "/Users/sej9799/Documents/projects/gengrove/benchmark/bedfiles/bed_10K_sorted.bed"});
    files.push_back({"100K", "/Users/sej9799/Documents/projects/gengrove/benchmark/bedfiles/bed_100K_sorted.bed"});
    files.push_back({"1M", "/Users/sej9799/Documents/projects/gengrove/benchmark/bedfiles/bed_1M_sorted.bed"});
    files.push_back({"2M", "/Users/sej9799/Documents/projects/gengrove/benchmark/bedfiles/bed_2M_sorted.bed"});
    files.push_back({"3M", "/Users/sej9799/Documents/projects/gengrove/benchmark/bedfiles/bed_3M_sorted.bed"});
    files.push_back({"4M", "/Users/sej9799/Documents/projects/gengrove/benchmark/bedfiles/bed_4M_sorted.bed"});
    files.push_back({"5M", "/Users/sej9799/Documents/projects/gengrove/benchmark/bedfiles/bed_5M_sorted.bed"});
    files.push_back({"6M", "/Users/sej9799/Documents/projects/gengrove/benchmark/bedfiles/bed_6M_sorted.bed"});
    files.push_back({"7M", "/Users/sej9799/Documents/projects/gengrove/benchmark/bedfiles/bed_7M_sorted.bed"});
    files.push_back({"8M", "/Users/sej9799/Documents/projects/gengrove/benchmark/bedfiles/bed_8M_sorted.bed"});
    files.push_back({"9M", "/Users/sej9799/Documents/projects/gengrove/benchmark/bedfiles/bed_9M_sorted.bed"});
    files.push_back({"10M", "/Users/sej9799/Documents/projects/gengrove/benchmark/bedfiles/bed_10M_sorted.bed"});

    genogrove::TypeRegistry::registerType<int>(); // register int type

    for(int i=0; i < files.size(); i++) {
        std::cout << "Benchmarking " << files[i].first << " file" << std::endl;
        for(int j=0; j < orders.size(); ++j) {
            auto startInsertion = std::chrono::steady_clock::now();
            std::cout << "order: " << orders[j] << std::endl;
            genogrove::IBPTree tree(orders[j]); // create the tree

            // iterate through file
            std::ifstream infile(files[i].second);
            std::string line;
            while(std::getline(infile, line)) {
                std::istringstream iss(line);
                std::string chrom;
                int start, end, data;
                iss >> chrom >> start >> end >> data;
                tree.insertData(chrom, genogrove::Interval{size_t(start), size_t(end)}, data);
            }
            auto endInsertion = std::chrono::steady_clock::now();
            std::chrono::duration<double> insertionDuration = endInsertion - startInsertion;
            std::cout << "Time taken for insertion: " << insertionDuration.count() << " seconds\n";

            // time the search
            auto startSearch = std::chrono::steady_clock::now();
            for(int i=0; i < 10; i++) {
                tree.overlaps("chr1", genogrove::Interval{size_t(i), size_t(i+100)});
            }
            auto endSearch = std::chrono::steady_clock::now();
            std::chrono::duration<double> searchDuration = endSearch - startSearch;
            std::cout << "Time taken for search: " << searchDuration.count() << " seconds\n\n";



        }
    }




//    for(auto& [key,value] : files) {
//        std::cout << "Benchmarking " << key << " file" << std::endl;
//        // time the insertion
//
//        for(int i=2; i <= 50; ++i) {
//            auto startInsertion = std::chrono::steady_clock::now();
//            std::cout << "order: " << i << std::endl;
//            genogrove::IBPTree tree(i); // create the tree
//
//            // iterate through the file
//            std::ifstream infile(value);
//            std::string line;
//            while(std::getline(infile, line)) {
//                std::istringstream iss(line);
//                std::string chrom;
//                int start, end, data;
//                iss >> chrom >> start >> end >> data;
//                std::cout << chrom << "\t" << start << "\t" << end << "\t" << data << std::endl;
//                tree.insertData(chrom, genogrove::Interval{size_t(start), size_t(end)}, data);
//            }
//            auto endInsertion = std::chrono::steady_clock::now();
//            std::chrono::duration<double> insertionDuration = endInsertion - startInsertion;
//            std::cout << "Time taken for insertion: " << insertionDuration.count() << " seconds\n";
//
//            // time the insertion
//        }
//    }


//        for(int i=2; i <= 50; ++i) {
            // create the tree
            //genogrove::TypeRegistry::registerType<int>();
            //genogrove::IBPTree tree(i);

            // iterate through the file
//            std::ifstream infile(file.second);
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
//            auto startInsertion = std::chrono::steady_clock::now();
//            for(int i=0; i < 100; i++) {
//                tree.insert(chrom, key);
//            }
//            auto endInsertion = std::chrono::steady_clock::now();
//            std::chrono::duration<double> insertionDuration = endInsertion - startInsertion;
//            std::cout << "Time taken for insertion: " << insertionDuration.count() << " seconds\n\n";
//
//            // time the search
//            auto startSearch = std::chrono::steady_clock::now();
//            for(int i=0; i < 100; i++) {
//                tree.search(chrom, intvl);
//            }
//            auto endSearch = std::chrono::steady_clock::now();
//            std::chrono::duration<double> searchDuration = endSearch - startSearch;
//            std::cout << "Time taken for search: " << searchDuration.count() << " seconds\n\n";

//        }
//    }



}