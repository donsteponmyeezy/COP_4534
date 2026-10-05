/**********************************************************************
  Student Name: Caleb Hughes
  File Name: file_handler.cpp
  Assignment number: Project 4
  File Description: Implementation of FileHandler class
                    Reads count and items from file, checks for 
                    valid sizes, and discards invalid items
**********************************************************************/

#include "file_handler.hpp"
#include <iostream>
#include <fstream>

/**************************************************************************************
 Function Name: FileHandler::FileHandler
  Description: Constructor for FileHandler
  Parameters: None
  Local Variables: None
**************************************************************************************/
FileHandler::FileHandler() {}

/**************************************************************************************
  Function Name: FileHandler::read_items
  Description: Opens file, reads initial count, then reads that many 
               floats. Validates that each float is between 0 and 1. Invalid items 
               are printed to console and discarded. Returns valid items from file
  Parameters: 
    - const std::string& filename: Name of text file to read from.
  Local Variables: 
    - std::vector<float> valid_items: Container to hold valid item sizes
    - std::ifstream file: Input file stream object for reading text file
    - int num_items: First integer in file dictating number of items following.
    - float current_item: Temporary variable to hold item currently being read
**************************************************************************************/
std::vector<float> FileHandler::read_items(const std::string& filename) {
    std::vector<float> valid_items;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Error: Could not open file " << filename << std::endl;
        return valid_items;
    }

    int num_items;
    // Read first int that indicates number of items following
    if (file >> num_items) {
        for (int i = 0; i < num_items; ++i) {
            float current_item;
            // Read subsequent items as float
            if (file >> current_item) {
                // Error checking: verify item is > 0 and <= 1
                if (current_item <= 0.0f || current_item > 1.0f) {
                    // Report invalid item and discard it
                    std::cout << "Error: Invalid item size " << current_item << " found. Discarding." << std::endl;
                    continue; // Continue processing rest of items in file
                }
                valid_items.push_back(current_item); // Add valid item to container
            }
        }
    }
    file.close();
    return valid_items; // Return vector of valid items from file
}