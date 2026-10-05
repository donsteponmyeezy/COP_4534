/**********************************************************************
  Student Name: Caleb Hughes
  File Name: file_handler.hpp
  Assignment number: Project 5
  File Description: Declarations for reading twoStrings.txt and
                    multiStrings.txt input layouts
**********************************************************************/

#ifndef FILE_HANDLER_HPP
#define FILE_HANDLER_HPP

#include <string>
#include <utility>
#include <vector>

// first non-empty line and second non-empty line from disk
std::pair<std::string, std::string> readTwoStrings(const std::string& path);

// leading count N then N non-empty lines, skipping blank lines
std::vector<std::string> readMultiStrings(const std::string& path);

#endif
