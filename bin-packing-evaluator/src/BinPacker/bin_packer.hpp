/**********************************************************************
  Student Name: Caleb Hughes
  File Name: bin_packer.hpp
  Assignment number: Project 4
  File Description: Header file for Bin and BinPacker classes
                    Defines the structure and function prototypes for 
                    online and offline bin packing algorithms 
                    and optimal solution generator
**********************************************************************/

#ifndef BIN_PACKER_HPP
#define BIN_PACKER_HPP

#include <vector>
#include <string>

// Represents single bin with capacity constraint
class Bin {
public:
    float remaining_capacity;
    std::vector<float> items;

    Bin();
};

// Class containing all bin packing algorithms, optimal solution generator, printing function
class BinPacker {
public:
    BinPacker();

    // Online algorithms: items processed as they arrive
    std::vector<Bin> online_first_fit(const std::vector<float>& items);
    std::vector<Bin> online_next_fit(const std::vector<float>& items);
    std::vector<Bin> online_best_fit(const std::vector<float>& items);
    
    // Offline algorithms: items sorted in descending order before packing
    std::vector<Bin> offline_first_fit(std::vector<float> items);
    std::vector<Bin> offline_best_fit(std::vector<float> items);
    
    // Brute-force search for optimal configuration
    std::vector<Bin> optimal_solution(std::vector<float> items);

    // Formats and prints packed bins
    void print_packing_details(const std::string& title, const std::vector<Bin>& bins);
};  

#endif