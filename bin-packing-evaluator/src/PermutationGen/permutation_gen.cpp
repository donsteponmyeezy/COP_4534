/**********************************************************************
  Student Name: Caleb Hughes
  File Name: permutation_gen.cpp
  Assignment number: Project 4
  File Description: Implementation of PermutationGen class. 
                    Uses required perm1 iterative algorithm to find 
                    next permutation for optimal solution
**********************************************************************/

#include "permutation_gen.hpp"
#include <algorithm>

/**************************************************************************************
 Function Name: PermutationGen::PermutationGen
  Description: Constructor for PermutationGen 
  Parameters: None
  Local Variables: None
**************************************************************************************/
PermutationGen::PermutationGen() {}

/**************************************************************************************
  Function Name: PermutationGen::perm1
  Description: Updates array to next permutation using iterative 
               algorithm from Project 3. Returns true if next 
               permutation exists, false if last permutation reached.
  Parameters: 
    - std::vector<float>& items: Reference to array of items to generate permutations for
  Local Variables: 
    - int n: Size of items array
    - int m, k, p, q: Indices used to find and swap elements for next permutation
**************************************************************************************/
bool PermutationGen::perm1(std::vector<float>& items) {
    int n = items.size();
    if (n <= 1) return false;

    int m = n - 2;
    
    // Find largest index m where items[m] < items[m + 1]
    while (m >= 0 && items[m] >= items[m + 1]) {
        m = m - 1;
    }

    // If no matching index found, last permutation reached
    if (m < 0) {
        return false; 
    }

    int k = n - 1;
    
    // Find largest index k > m where items[m] < items[k]
    while (items[m] >= items[k]) {
        k = k - 1;
    }

    // Swap values of items[m] with items[k]
    std::swap(items[m], items[k]);

    // Reverse sequence from items[m + 1] up to and including final element
    int p = m + 1;
    int q = n - 1;
    while (p < q) {
        std::swap(items[p], items[q]);
        p++;
        q--;
    }

    return true;
}