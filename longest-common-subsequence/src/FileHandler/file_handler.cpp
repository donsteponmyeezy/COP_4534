/**********************************************************************
  Student Name: Caleb Hughes
  File Name: file_handler.cpp
  Assignment number: Project 5
  File Description: Implementation of file helpers for given input files
**********************************************************************/

#include "file_handler.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>

namespace {

std::string trimTrailingCr(std::string s) {
    if (!s.empty() && s.back() == '\r') {
        s.pop_back();
    }
    return s;
}

std::string readNonEmptyLine(std::istream& in, const char* ctx) {
    std::string line;
    while (std::getline(in, line)) {
        line = trimTrailingCr(line);
        if (!line.empty()) {
            return line;
        }
    }
    throw std::runtime_error(std::string("Unexpected EOF while reading: ") + ctx);
}

}

std::pair<std::string, std::string> readTwoStrings(const std::string& path) {
    std::ifstream in(path);
    if (!in) {
        throw std::runtime_error("failed to open file: " + path);
    }
    std::string a = readNonEmptyLine(in, "first string in twoStrings file");
    std::string b = readNonEmptyLine(in, "second string in twoStrings file");
    return {a, b};
}

std::vector<std::string> readMultiStrings(const std::string& path) {
    std::ifstream in(path);
    if (!in) {
        throw std::runtime_error("failed to open file: " + path);
    }

    std::string countLine = readNonEmptyLine(in, "string count in multiStrings file");
    std::istringstream countStream(countLine);
    int n = 0;
    countStream >> n;
    if (!countStream || n < 0) {
        throw std::runtime_error("invalid string count: " + path);
    }

    std::vector<std::string> out;
    out.reserve(static_cast<std::size_t>(n));
    for (int i = 0; i < n; ++i) {
        out.push_back(readNonEmptyLine(in, "data string in multiStrings file"));
    }
    return out;
}
