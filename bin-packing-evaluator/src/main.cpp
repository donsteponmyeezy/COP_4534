/**********************************************************************
  Student Name: Caleb Hughes
  File Name: main.cpp
  Assignment number: Project 4
  File Description: Main driver for Bin Packing project
                    Reads items, runs all bin packing algorithms, 
                    formats output table and bin details
**********************************************************************/

#include "BinPacker/bin_packer.hpp"
#include "FileHandler/file_handler.hpp"
#include <iostream>
#include <iomanip>
#include <vector>

int main() {
    FileHandler file_handler;
    BinPacker bin_packer;

    // Read and validate items from input text file
    std::vector<float> items = file_handler.read_items("items.txt");

    if (items.empty()) {
        std::cout << "No valid items to pack. Exiting." << std::endl;
        return 1;
    }

    // Run all binpacking algorithms
    std::vector<Bin> optimal = bin_packer.optimal_solution(items);
    
    std::vector<Bin> online_ff = bin_packer.online_first_fit(items);
    std::vector<Bin> online_nf = bin_packer.online_next_fit(items);
    std::vector<Bin> online_bf = bin_packer.online_best_fit(items);
    
    std::vector<Bin> offline_ff = bin_packer.offline_first_fit(items);
    std::vector<Bin> offline_bf = bin_packer.offline_best_fit(items);

    // Print summary table of bin packing results
    std::cout << std::left << std::setw(30) << "Policy" << "Total Bins Used" << std::endl;
    std::cout << std::left << std::setw(30) << "Optimal Solution" << optimal.size() << std::endl;
    
    std::cout << "Online Algorithm" << std::endl;
    std::cout << std::left << std::setw(30) << "     First Fit" << online_ff.size() << std::endl;
    std::cout << std::left << std::setw(30) << "     Next Fit" << online_nf.size() << std::endl;
    std::cout << std::left << std::setw(30) << "     Best Fit" << online_bf.size() << std::endl;
    
    std::cout << "Offline Algorithm" << std::endl;
    std::cout << std::left << std::setw(30) << "     First Fit" << offline_ff.size() << std::endl;
    std::cout << std::left << std::setw(30) << "     Best Fit" << offline_bf.size() << std::endl;
    std::cout << std::endl;

    // Print detailed bin packing details
    bin_packer.print_packing_details("Optimal", optimal);
    bin_packer.print_packing_details("Online First Fit", online_ff);
    bin_packer.print_packing_details("Online Next Fit", online_nf);
    bin_packer.print_packing_details("Online Best Fit", online_bf);
    bin_packer.print_packing_details("Offline First Fit", offline_ff);
    bin_packer.print_packing_details("Offline Best Fit", offline_bf);

    return 0;
}