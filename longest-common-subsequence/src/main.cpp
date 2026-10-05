/**********************************************************************
  Student Name: Caleb Hughes
  File Name: main.cpp
  Assignment number: Project 5
  File Description: Program entry, part1 & part2 runner,
                    usage text, error handling
**********************************************************************/

#include "FileHandler/file_handler.hpp"
#include "LCSEvaluator/lcs_evaluator.hpp"

#include <iostream>
#include <string>

namespace {

// prints argv0 and expected arguments
void printUsage(const char* argv0) {
    std::cerr << "Usage:\n"
              << "  " << argv0 << " part1 [two_strings_file]\n"
              << "  " << argv0 << " part2 [multi_strings_file]\n"
              << "Defaults: twoStrings.txt and multiStrings.txt in the current directory.\n";
}

// full c matrix part and stdout report
void runPart1(const std::string& path) {
    const auto [x, y] = readTwoStrings(path);
    const Part1Result r = evaluatePart1FullMatrix(x, y);

    std::cout << "=== Part 1: Full LCS matrix (traceback from c only) ===\n\n";
    std::cout << "String X (" << r.x.size() << " chars):\n" << r.x << "\n\n";
    std::cout << "String Y (" << r.y.size() << " chars):\n" << r.y << "\n\n";
    std::cout << "LCS length: " << r.lcs_length << "\n";
    std::cout << "LCS subsequence:\n" << r.lcs_subsequence << "\n";
}

// two row lcs and similarity table
void runPart2(const std::string& path) {
    const std::vector<std::string> strings = readMultiStrings(path);
    const auto table = pairwiseLcsLengths(strings);

    std::cout << "=== Part 2: Memory-optimized pairwise LCS (2-row DP) ===\n\n";
    std::cout << "Loaded " << strings.size() << " strings.\n";
    for (std::size_t i = 0; i < strings.size(); ++i) {
        std::cout << "  [" << i << "] length " << strings[i].size() << "\n";
    }
    printPart2SimilarityTable(strings, table);
}

}

int main(int argc, char** argv) {
    if (argc < 2) {
        printUsage(argv[0]);
        return 1;
    }
    const std::string mode = argv[1];
    try {
        if (mode == "part1") {
            const std::string path = argc >= 3 ? argv[2] : "twoStrings.txt";
            runPart1(path);
            return 0;
        }
        if (mode == "part2") {
            const std::string path = argc >= 3 ? argv[2] : "multiStrings.txt";
            runPart2(path);
            return 0;
        }
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
        return 2;
    }

    printUsage(argv[0]);
    return 1;
}
