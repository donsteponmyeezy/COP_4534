/**********************************************************************
  Student Name: Caleb Hughes
  File Name: file_handler.hpp
  Assignment number: Project 4
  File Description: Header file for FileHandler class
                    Reads and validates items from input text file
**********************************************************************/

#ifndef FILE_HANDLER_HPP
#define FILE_HANDLER_HPP

#include <vector>
#include <string>

// Class to handle reading input files for bin packing
class FileHandler {
public:
    FileHandler();

    // Reads items from file, validates them, and returns as vector
    std::vector<float> read_items(const std::string& filename);
};

#endif