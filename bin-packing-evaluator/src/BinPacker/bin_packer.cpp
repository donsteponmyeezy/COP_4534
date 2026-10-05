/**********************************************************************
  Student Name: Caleb Hughes
  File Name: bin_packer.cpp
  Assignment number: Project 4
  File Description: Implementation of BinPacker class. Contains   
                    all greedy algorithms(First Fit, Next Fit, Best Fit) 
                    for both online and offline bin packing, as well as 
                    the optimal solution generator
**********************************************************************/

#include "bin_packer.hpp"
#include "../PermutationGen/permutation_gen.hpp"

#include <iostream>
#include <algorithm>
#include <functional>

/**************************************************************************************
 Function Name: Bin::Bin
  Description: Constructor for Bin struct. Initializes new bin with standard capacity of 1.0 unit.
  Parameters: None
  Local Variables: None
**************************************************************************************/
Bin::Bin() {
    remaining_capacity = 1.0f;
}

/************************************************************************************** 
  Function Name: BinPacker::BinPacker
  Description: Constructor for BinPacker
  Parameters: None
  Local Variables: None
**************************************************************************************/
BinPacker::BinPacker() {}

/************************************************************************************** 
  Function Name: BinPacker::online_first_fit
  Description: Implements Online First Fit algorithm. Scans open 
               bins and places item in the first one that fits
  Parameters: 
    - const std::vector<float>& items: Constant reference to text file 
      of items converted to array of items to pack in bins
  Local Variables: 
    - std::vector<Bin> bins: Container for currently open bins
    - bool placed: Flag to track if current item successfully fit in an existing bin
    - Bin new_bin: Fresh bin instance created if all current bins are too full
**********************************************************************/
std::vector<Bin> BinPacker::online_first_fit(const std::vector<float>& items) {
    std::vector<Bin> bins;
    for (float item : items) {
        bool placed = false;
        for (Bin& bin : bins) {
            if (item <= bin.remaining_capacity) {
                bin.items.push_back(item);
                bin.remaining_capacity -= item;
                placed = true;
                break;
            }
        }
        if (!placed) {
            Bin new_bin;
            new_bin.items.push_back(item);
            new_bin.remaining_capacity -= item;
            bins.push_back(new_bin);
        }
    }
    return bins;
}

/**************************************************************************************
  Function Name: BinPacker::online_next_fit
  Description: Implements Online Next Fit heuristic. Only checks 
               most recently opened bin. If item doesn't fit, new bin is created
  Parameters: 
    - const std::vector<float>& items: Constant reference to the array of items to pack.
  Local Variables: 
    - std::vector<Bin> bins: Container for all currently open bins
    - Bin new_bin: Freshly instantiated bin if prev bin too full.
**************************************************************************************/
std::vector<Bin> BinPacker::online_next_fit(const std::vector<float>& items) {
    std::vector<Bin> bins;
    for (float item : items) {
        if (bins.empty() || item > bins.back().remaining_capacity) { // Computationally efficient to check if the bin is empty first
            Bin new_bin;
            new_bin.items.push_back(item);
            new_bin.remaining_capacity -= item;
            bins.push_back(new_bin);
        } else {
            bins.back().items.push_back(item);
            bins.back().remaining_capacity -= item;
        }
    }
    return bins;
}

/**************************************************************************************
  Function Name: BinPacker::online_best_fit
  Description: Implements Online Best Fit heuristic. Scans open bins and 
               places item in bin where it fits the tightest (leaves the 
               least remaining space). If it fits nowhere, opens new bin.
  Parameters: 
    - const std::vector<float>& items: Constant reference to array of items to pack
  Local Variables: 
    - std::vector<Bin> bins: Container for currently open bins
    - int best_idx: Index of the bin that offers the tightest fit
    - float min_space: Tracks the minimum remaining capacity found so far
    - float leftover: Temporary calculation of remaining space if placed in bin
    - Bin new_bin: Freshly instantiated bin if item doesn't fit in open bins
**************************************************************************************/
std::vector<Bin> BinPacker::online_best_fit(const std::vector<float>& items) {
  std::vector<Bin> bins;
  for (float item : items) {
      int best_idx = -1;
      float min_space = 2.0f; 

      for (size_t i = 0; i < bins.size(); ++i) {
          if (item <= bins[i].remaining_capacity) {
              float leftover = bins[i].remaining_capacity - item;
              if (leftover < min_space) {
                  min_space = leftover;
                  best_idx = i;
              }
          }
      }

      if (best_idx != -1) {
          bins[best_idx].items.push_back(item);
          bins[best_idx].remaining_capacity -= item;
      } else {
          Bin new_bin;
          new_bin.items.push_back(item);
          new_bin.remaining_capacity -= item;
          bins.push_back(new_bin);
      }
  }
  return bins;
}

/**************************************************************************************
  Function Name: BinPacker::offline_first_fit
  Description: Implements Offline First Fit algorithm. First sorts 
               items in descending order, then delegates packing to 
               online_first_fit algorithm.
  Parameters: 
    - std::vector<float> items: Copy of items array to allow for sorting
  Local Variables: None
**************************************************************************************/
std::vector<Bin> BinPacker::offline_first_fit(std::vector<float> items) {
  std::sort(items.begin(), items.end(), std::greater<float>());
  return online_first_fit(items);
}

/**************************************************************************************
  Function Name: BinPacker::offline_best_fit
  Description: Implements Offline Best Fit heuristic. Sorts items in descending order,
               then delegates packing to online_best_fit algorithm.
  Parameters: 
    - std::vector<float> items: Copy of items array to allow for sorting
  Local Variables: None
**************************************************************************************/
std::vector<Bin> BinPacker::offline_best_fit(std::vector<float> items) {
  std::sort(items.begin(), items.end(), std::greater<float>());
  return online_best_fit(items);
}


/**************************************************************************************
  Function Name: BinPacker::optimal_solution
  Description: Brute-force searches for optimal bin packing solution by 
               generating all permutations of items array and evaluating 
               them using next fit. Keeps track of configuration that uses 
               minimum number of bins.
  Parameters: 
    - std::vector<float> items: Copy of items array to allow sorting 
      and generating all permutations
  Local Variables: 
    - PermutationGen p_gen: Instance of permutation generator
    - std::vector<Bin> best_packing: Stores packing configuration with minimum bins
    - size_t min_bins: Tracks current lowest number of bins used
    - std::vector<Bin> current_packing: Temporary storage for evaluating current 
      packing configuration
**************************************************************************************/
std::vector<Bin> BinPacker::optimal_solution(std::vector<float> items) {
  std::sort(items.begin(), items.end());
  
  PermutationGen p_gen;
  std::vector<Bin> best_packing;
  size_t min_bins = items.size() + 1;

  do {
      std::vector<Bin> current_packing = online_next_fit(items);
      if (current_packing.size() < min_bins) {
          min_bins = current_packing.size();
          best_packing = current_packing;
      }
  } while (p_gen.perm1(items));

  return best_packing;
}

/**************************************************************************************
  Function Name: BinPacker::print_packing_details
  Description: Formats and prints final bin packing results
  Parameters: 
    - const std::string& title: Heading/label of bin packing details
    - const std::vector<Bin>& bins: Constant reference to packed bins
  Local Variables: None
**************************************************************************************/
void BinPacker::print_packing_details(const std::string& title, const std::vector<Bin>& bins) {
  std::cout << title << ":" << std::endl;
  for (size_t i = 0; i < bins.size(); ++i) {
      std::cout << "  b" << (i + 1) << ": ";
      for (size_t j = 0; j < bins[i].items.size(); ++j) {
          std::cout << bins[i].items[j];
          if (j < bins[i].items.size() - 1) std::cout << ", ";
      }
      std::cout << std::endl;
  }
  std::cout << std::endl;
}