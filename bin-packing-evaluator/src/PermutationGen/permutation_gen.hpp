/**********************************************************************
  Student Name: Caleb Hughes
  File Name: permutation_gen.hpp
  Assignment number: Project 4
  File Description: Header file for PermutationGen class
                    Defines the structure for generating permutations
                    using the required iterative algorithm from Project 3
**********************************************************************/

#ifndef PERMUTATION_GEN_HPP
#define PERMUTATION_GEN_HPP

#include <vector>

// Class to generate permutations for array items
class PermutationGen {
public:
    PermutationGen();

    // Generates next permutation of array using the perm1 algorithm
    bool perm1(std::vector<float>& items);
};

#endif