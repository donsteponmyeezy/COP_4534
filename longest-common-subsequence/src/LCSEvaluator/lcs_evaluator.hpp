/**********************************************************************
  Student Name: Caleb Hughes
  File Name: lcs_evaluator.hpp
  Assignment number: Project 5
  File Description: LCS dynamic programming and part 2 similarity
                    declarations and part 1 result struct
**********************************************************************/

#ifndef LCS_EVALUATOR_HPP
#define LCS_EVALUATOR_HPP

#include <string>
#include <vector>

// strings, lcs length, and reconstructed subsequence from part 1
struct Part1Result {
    std::string x;
    std::string y;
    int lcs_length{};
    std::string lcs_subsequence;
};

// flattened (m+1)(n+1) c table; traceback uses c only, no b array
Part1Result evaluatePart1FullMatrix(const std::string& x, const std::string& y);

// two rolling rows of length n+1 for part 2 length only
int lcsLengthTwoRow(const std::string& x, const std::string& y);

// all pairs i j lcs lengths stored symmetrically
std::vector<std::vector<int>> pairwiseLcsLengths(const std::vector<std::string>& strings);

// h m l d label from assignment length and lcs ratio rules
char classifySimilarity(const std::string& a, const std::string& b, int lcs_length);

void printPart2SimilarityTable(const std::vector<std::string>& strings,
                               const std::vector<std::vector<int>>& lcs_table);

#endif
